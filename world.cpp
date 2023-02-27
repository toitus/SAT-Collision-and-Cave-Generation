#include "world.hpp"

World::World() {
    if (boxtexture.loadFromFile("content/player.png")) {
        box.setTexture(&boxtexture);
        boxy.setTexture(&boxtexture);
        boxyy.setTexture(&boxtexture);
        box.setSize(sf::Vector2f(32, 32));
        boxy.setSize(sf::Vector2f(32, 32));
        boxyy.setSize(sf::Vector2f(32, 32));
        box.setType("dynamic");
        boxy.setType("dynamic");
        boxyy.setType("dynamic");
    }
    entities.push_back(&player);
    entities.push_back(&box);
    entities.push_back(&boxy);
    entities.push_back(&boxyy);
    map.generate();
    player.position(map.getRandomEmptyTilePosition());
    box.position(map.getRandomEmptyTilePosition());
    boxy.position(map.getRandomEmptyTilePosition());
    boxyy.position(map.getRandomEmptyTilePosition());
}

void World::events(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            map.generate();
            player.position(map.getRandomEmptyTilePosition());
            box.position(map.getRandomEmptyTilePosition());
            boxy.position(map.getRandomEmptyTilePosition());
            boxyy.position(map.getRandomEmptyTilePosition());
        }
    }
}

void World::update(float dt, sf::View& view) {
    player.update(dt);

    checkCollisions();

    //* updates view to follow player at a specified speed
    sf::Vector2f target = player.center();
    sf::Vector2f current = view.getCenter();
    sf::Vector2f difference = target - current;
    float speed = 2.5f;
    sf::Vector2f offset = sf::Vector2f(difference.x, difference.y);
    if (offset.x < 0.3f && offset.x > -0.3f) offset.x = 0.f;
    if (offset.y < 0.3f && offset.y > -0.3f) offset.y = 0.f;
    view.setCenter(current+offset);
    //* 
}

void World::draw(sf::RenderWindow& window) {
    map.draw(window);
    box.draw(window);
    boxy.draw(window);
    boxyy.draw(window);
    player.draw(window);
}

void World::checkCollisions() {
    //push dyamics along player axis if collisions exist
    //player is at location 0 in entities vector
    for (int i = 1; i < entities.size(); ++i) {
        sf::Vector2f mtv = getMTV(entities[i], entities[0]);
        if (mtv != sf::Vector2f(0, 0)) {
            entities[i]->move(mtv);
            resolveCollisions(entities[i]);
        }
    }

    //determine which dynamics collide against static tiles
    //and push back along static axis if collisions exist
    for (int i = 0; i < entities.size(); ++i) {
        int row = static_cast<int>(entities[i]->center().y / map.getTilesize());
        int column = static_cast<int>(entities[i]->center().x / map.getTilesize());

        if (map.getTile(row-1, column)->getType() == "static") {
            sf::Vector2f top = getMTV(entities[i], map.getTile(row-1, column));
            if (top != sf::Vector2f(0, 0)) { entities[i]->move(top); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row+1, column)->getType() == "static") {
            sf::Vector2f bottom = getMTV(entities[i], map.getTile(row+1, column));
            if (bottom != sf::Vector2f(0, 0)) { entities[i]->move(bottom); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row, column-1)->getType() == "static") {
            sf::Vector2f left = getMTV(entities[i], map.getTile(row, column-1));
            if (left != sf::Vector2f(0, 0)) { entities[i]->move(left); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row, column+1)->getType() == "static") {
            sf::Vector2f right = getMTV(entities[i], map.getTile(row, column+1));
            if (right != sf::Vector2f(0, 0)) { entities[i]->move(right); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row-1, column-1)->getType() == "static") {
            sf::Vector2f topleft = getMTV(entities[i], map.getTile(row-1, column-1));
            if (topleft != sf::Vector2f(0, 0)) { entities[i]->move(topleft); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row+1, column-1)->getType() == "static") {
            sf::Vector2f bottomleft = getMTV(entities[i], map.getTile(row+1, column-1));
            if (bottomleft != sf::Vector2f(0, 0)) { entities[i]->move(bottomleft); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row-1, column+1)->getType() == "static") {
            sf::Vector2f topright = getMTV(entities[i], map.getTile(row-1, column+1));
            if (topright != sf::Vector2f(0, 0)) { entities[i]->move(topright); resolveCollisions(entities[i]); }
        }

        if (map.getTile(row+1, column+1)->getType() == "static") {
            sf::Vector2f bottomright = getMTV(entities[i], map.getTile(row+1, column+1));
            if (bottomright != sf::Vector2f(0, 0)) { entities[i]->move(bottomright); resolveCollisions(entities[i]); }
        }
    }
}

//recursively resolve a collision chain at root s
void World::resolveCollisions(Sprite* s) {
    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i] != s) {
            sf::Vector2f mtv = getMTV(entities[i], s);
            if (mtv != sf::Vector2f(0, 0)) {
                entities[i]->move(mtv);
                resolveCollisions(entities[i]);
            }
        }
    }
}

sf::Vector2f World::getMTV(Sprite* a, Sprite* b) {
    float aMin, aMax;
    float bMin, bMax;
    float minOverlap = 1000;
    int minOverlapAxis;
    sf::Vector2f mtv = sf::Vector2f(0, 0);

    sf::Vector2f aTopLeft(a->left(), a->top());
    sf::Vector2f aTopRight(a->right(), a->top());
    sf::Vector2f aBotLeft(a->left(), a->bottom());
    sf::Vector2f aBotRight(a->right(), a->bottom());

    sf::Vector2f bTopLeft(b->left(), b->top());
    sf::Vector2f bTopRight(b->right(), b->top());
    sf::Vector2f bBotLeft(b->left(), b->bottom());
    sf::Vector2f bBotRight(b->right(), b->bottom());

    for (int i = 0; i < separatingAxes.size(); ++i) {
        float aTopLeftDot = dot(aTopLeft, separatingAxes[i]);
        float aTopRightDot = dot(aTopRight, separatingAxes[i]);
        float aBotLeftDot = dot(aBotLeft, separatingAxes[i]);
        float aBotRightDot = dot(aBotRight, separatingAxes[i]);
        aMin = std::min(aTopLeftDot, std::min(aTopRightDot, std::min(aBotLeftDot, aBotRightDot)));
        aMax = std::max(aTopLeftDot, std::max(aTopRightDot, std::max(aBotLeftDot, aBotRightDot)));

        float bTopLeftDot = dot(bTopLeft, separatingAxes[i]);
        float bTopRightDot = dot(bTopRight, separatingAxes[i]);
        float bBotLeftDot = dot(bBotLeft, separatingAxes[i]);
        float bBotRightDot = dot(bBotRight, separatingAxes[i]);
        bMin = std::min(bTopLeftDot, std::min(bTopRightDot, std::min(bBotLeftDot, bBotRightDot)));
        bMax = std::max(bTopLeftDot, std::max(bTopRightDot, std::max(bBotLeftDot, bBotRightDot)));

        if (aMax < bMin || bMax < aMin) {
            return mtv;
        }

        if ((bMax - aMin) < minOverlap) {
            minOverlap = bMax - aMin;
            minOverlapAxis = i;
        }
    }

    mtv.x = minOverlap * separatingAxes[minOverlapAxis].x;
    mtv.y = minOverlap * separatingAxes[minOverlapAxis].y; 

    return mtv; 
}

float World::dot(sf::Vector2f a, sf::Vector2f b) {
    return (a.x * b.x) + (a.y * b.y);
}
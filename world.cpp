#include "world.hpp"

World::World() {
    player.position(sf::Vector2f(0, 0));
}

void World::events(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            map.generate();
        }
    }
}

void World::update(float dt, sf::View& view) {
    player.update(dt);

    //* updates view to follow player at a specified speed
    sf::Vector2f target = player.center();
    sf::Vector2f current = view.getCenter();
    sf::Vector2f difference = target - current;
    float speed = 2.5f;
    sf::Vector2f offset = sf::Vector2f(difference.x * dt * speed, difference.y * dt * speed);
    if (offset.x < 0.3f && offset.x > -0.3f) offset.x = 0.f;
    if (offset.y < 0.3f && offset.y > -0.3f) offset.y = 0.f;
    view.move(offset);
    //* 
}

void World::draw(sf::RenderWindow& window) {
    map.draw(window);
    player.draw(window);
}

void World::checkCollisions() {

}

/*void World::resolveCollisions() {
    float aMin, aMax;
    float bMin, bMax;
    float minOverlap = 1000;
    int minOverlapAxis;
    sf::Vector2f mtv;

    sf::Vector2f aTopLeft(root->left(), root->top());
    sf::Vector2f aTopRight(root->right(), root->top());
    sf::Vector2f aBotLeft(root->left(), root->bottom());
    sf::Vector2f aBotRight(root->right(), root->bottom());

    for (int a = 0; a < entities.size(); ++a) {

    }

    for (int e = 0; e < entities.size(); ++e) {
        if () {
            sf::Vector2f bTopLeft(entities[e]->left(), entities[e]->top());
            sf::Vector2f bTopRight(entities[e]->right(), entities[e]->top());
            sf::Vector2f bBotLeft(entities[e]->left(), entities[e]->bottom());
            sf::Vector2f bBotRight(entities[e]->right(), entities[e]->bottom());

            int overlaps = 0;
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
                    break;
                }

                overlaps++;
                if ((bMax - aMin) < minOverlap) {
                    minOverlap = bMax - aMin;
                    minOverlapAxis = i;
                }
            }

            if (overlaps == 4) {
                mtv.x = minOverlap * separatingAxes[minOverlapAxis].x;
                mtv.y = minOverlap * separatingAxes[minOverlapAxis].y; 
            }
        }
    }
}*/

float World::dot(sf::Vector2f a, sf::Vector2f b) {
    return (a.x * b.x) + (a.y * b.y);
}
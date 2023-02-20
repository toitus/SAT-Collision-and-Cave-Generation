#include "world.hpp"

World::World() {
    a.position(sf::Vector2f(50, 70));
    b.position(sf::Vector2f(50, 115));

    entities.push_back(&player);
    entities.push_back(&a);
    entities.push_back(&b);
}

void World::update(float dt, sf::View& view) {
    player.update(dt);

    resolveCollisions();

    //* updates view to follow player at a specified speed
    sf::Vector2f target = player.center();
    sf::Vector2f current = view.getCenter();
    sf::Vector2f difference = target - current;
    float speed = 3.f;
    sf::Vector2f offset = difference * dt * speed;
    if (offset.x > -0.3 && offset.x < 0.3) { offset.x = 0; } //* eliminates view jitters when
    if (offset.y > -0.3 && offset.y < 0.3) { offset.y = 0; } //* camera closes in on player position
    view.move(offset);
    //* 
}

void World::draw(sf::RenderWindow& window) {
    a.draw(window);
    b.draw(window);
    player.draw(window);
}

void World::resolveCollisions() {
    for (int e = 0; e < entities.size(); ++e) {
        for (int i = 0; i < entities.size(); ++i) {
            if (i != e && i > e) {
                checkCollision(entities[e], entities[i]);
            }
        }
    }
}

bool World::checkCollision(Sprite* a, Sprite* b) {
    float aMin, aMax;
    float bMin, bMax;
    float minOverlap = 1000;
    int minOverlapAxis;
    sf::Vector2f mtv;

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
            return false;
        }

        if ((bMax - aMin) < minOverlap) {
            minOverlap = bMax - aMin;
            minOverlapAxis = i;
        }
    }

    mtv.x = minOverlap * separatingAxes[minOverlapAxis].x;
    mtv.y = minOverlap * separatingAxes[minOverlapAxis].y;

    if (a->getType() < b->getType()) {
        a->move(mtv);
    } else if (b->getType() < a->getType()) {
        b->move(mtv);
    }

    return true;
}

float World::dot(sf::Vector2f a, sf::Vector2f b) {
    return (a.x * b.x) + (a.y * b.y);
}
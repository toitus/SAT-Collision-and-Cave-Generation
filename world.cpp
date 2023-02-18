#include "world.hpp"

World::World() {
    a.position(sf::Vector2f(50, 70));
    b.position(sf::Vector2f(50, 115));
}

void World::update(float dt, sf::View& view) {
    player.update(dt);

    //* updates view to follow player at a specified speed
    sf::Vector2f target = player.center();
    sf::Vector2f current = view.getCenter();
    sf::Vector2f difference = target - current;
    float speed = 3.f;
    sf::Vector2f offset = difference * dt * speed;
    if (offset.x > -0.3 && offset.x < 0.3) { offset.x = 0; } //* eliminates view jitters
    if (offset.y > -0.3 && offset.y < 0.3) { offset.y = 0; }
    view.move(offset);
    //* 
}

void World::draw(sf::RenderWindow& window) {
    a.draw(window);
    b.draw(window);
    player.draw(window);
}
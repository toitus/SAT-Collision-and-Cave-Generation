#include "world.hpp"

World::World() {
    a.set_position(sf::Vector2f(50, 70));
    b.set_position(sf::Vector2f(50, 115));
}

void World::update(float dt) {
    player.update(dt);
}

void World::draw(sf::RenderWindow* w) {
    a.draw(w);
    b.draw(w);
    player.draw(w);
}
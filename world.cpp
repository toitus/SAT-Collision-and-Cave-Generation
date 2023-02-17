#include "world.hpp"

void World::update(float dt) {
    player.update(dt);
}

void World::draw(sf::RenderWindow* w) {
    player.draw(w);
}
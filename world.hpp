#pragma once

#include "player.hpp"
#include "tile.hpp"

class World {
    public:
        World();

        void update(float dt, sf::View& view);
        void draw(sf::RenderWindow& window);

    private:

        Player player;
        Tile a;
        Tile b;
};
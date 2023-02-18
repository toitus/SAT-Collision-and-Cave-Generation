#pragma once

#include "player.hpp"
#include "tile.hpp"

class World {
    public:
        World();

        sf::Vector2f player_center() { return player.center(); }

        void update(float dt);
        void draw(sf::RenderWindow* w);

    private:

        Player player;
        Tile a;
        Tile b;
};
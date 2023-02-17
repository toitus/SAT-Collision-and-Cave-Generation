#pragma once

#include "player.hpp"

class World {
    public:

        sf::Vector2f player_center() { return player.center(); }

        void update(float dt);
        void draw(sf::RenderWindow* w);

    private:

        Player player;
};
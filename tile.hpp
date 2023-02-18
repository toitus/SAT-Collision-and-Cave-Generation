#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

class Tile : public Sprite {
    public:
        Tile();

        void update(float dt);
        void draw(sf::RenderWindow& window);
};
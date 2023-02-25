#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

class Tile : public Sprite {
    public:
        int cavern;
        bool removable = true;
        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }
};
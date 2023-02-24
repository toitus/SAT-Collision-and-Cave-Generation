#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

class Tile : public Sprite {
    public:
        int cavern;

        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }
};
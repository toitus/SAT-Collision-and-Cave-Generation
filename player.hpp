#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

class Player : public Sprite {
    public:
        Player();

        void update(float dt);
        void draw(sf::RenderWindow& window);
    private:
        void movement(float dt);
        sf::Texture texture;

};
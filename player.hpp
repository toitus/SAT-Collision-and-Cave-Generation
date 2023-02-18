#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

class Player : public Sprite {
    public:
        Player();

        void update(float dt);
        void draw(sf::RenderWindow* w);
    private:
        void movement(float dt);

};
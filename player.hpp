#pragma once

#include <SFML/Graphics.hpp>

class Player {
    public:
        sf::Vector2f center();

        void update(float dt);
        void draw(sf::RenderWindow* w);
    private:

        void movement(float dt);

};

//todo
//add player sprite
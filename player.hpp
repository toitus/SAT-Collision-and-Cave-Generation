#pragma once

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player();
        void update(float dt, sf::View* v);
        void draw(sf::RenderWindow* w);

        sf::Vector2f get_center() { 
            return rectangle.getPosition() + half_size; 
        }

    private:
        sf::RectangleShape rectangle;
        sf::Vector2f size = sf::Vector2f(50.f, 50.f);
        sf::Vector2f half_size = sf::Vector2f(25.f, 25.f);

        bool w, a, s, d;
        void movement_input();
        void apply_movement(float dt);
};
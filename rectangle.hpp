#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "entity.hpp"

class Rectangle : public Entity {
    public:
        Rectangle();
        std::vector<sf::Vector2f> get_points();
        std::vector<sf::Vector2f> get_separating_axes();

        void update(float dt);
        void draw(sf::RenderWindow* w);
};
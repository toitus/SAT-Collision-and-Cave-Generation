#pragma once

#include <math.h>

class Entity {
    public:
        virtual std::vector<sf::Vector2f> get_points(sf::Vector2f p) = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow* w) = 0;
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f size;
        std::vector<sf::Vector2f> points;
};
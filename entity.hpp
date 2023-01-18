#pragma once

#include <math.h>

class Entity {
    public:
        virtual std::vector<sf::Vector2f> get_points() = 0;
        virtual std::vector<sf::Vector2f> get_separating_axes() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow* w) = 0;
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f size;
        std::vector<sf::Vector2f> points;
        std::vector<sf::Vector2f> separating_axes;

        sf::Vector2f normalize(sf::Vector2f v) {
            sf::Vector2f tv = v;
            float length = sqrt((tv.x*tv.x) + (tv.y*tv.y));
            if (length != 0) {
                tv.x /= length;
                tv.y /= length;
            }
            return tv;
        }
};
#pragma once 

#include <SFML/Graphics.hpp>

class Sprite {
    public:
        void set_position(sf::Vector2f p) { sprite.setPosition(p); }

        sf::Vector2f center() { return sprite.getPosition() + size/2.f; }
        float left() { return sprite.getPosition().x; }
        float right() { return sprite.getPosition().x + size.x; }
        float top() { return sprite.getPosition().y; }
        float bottom() { return sprite.getPosition().y + size.y; }

    protected:
        sf::Texture texture;
        sf::Sprite sprite; 
        sf::Vector2f size;
};
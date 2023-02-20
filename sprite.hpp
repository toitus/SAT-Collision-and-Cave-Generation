#pragma once 

#include <SFML/Graphics.hpp>

class Sprite {
    public:
        void move(sf::Vector2f offset) { sprite.move(offset); }
        void position(sf::Vector2f position) { sprite.setPosition(position); }

        sf::Vector2f center() { return sprite.getPosition() + size/2.f; }
        float left() { return sprite.getPosition().x; }
        float right() { return sprite.getPosition().x + size.x; }
        float top() { return sprite.getPosition().y; }
        float bottom() { return sprite.getPosition().y + size.y; }
        int getType() { return type; }

    protected:
        sf::Texture texture;
        sf::Sprite sprite; 
        sf::Vector2f size;
        int type; //collision priority: lower values get moved in resolution
};
#pragma once 

#include <SFML/Graphics.hpp>

class Sprite {
    public:
        virtual void draw(sf::RenderWindow& window) = 0;

        void setTexture(sf::Texture* t) { sprite.setTexture(*t); }
        void setTextureRect(sf::IntRect r) { sprite.setTextureRect(r); }

        void move(sf::Vector2f offset) { sprite.move(offset); }
        void position(sf::Vector2f position) { sprite.setPosition(position); }

        sf::Vector2f center() { return sprite.getPosition() + size/2.f; }
        float left() { return sprite.getPosition().x; }
        float right() { return sprite.getPosition().x + size.x; }
        float top() { return sprite.getPosition().y; }
        float bottom() { return sprite.getPosition().y + size.y; }
        sf::FloatRect bounds() { return sprite.getGlobalBounds(); }
        
        void setType(std::string t) { type = t; }
        std::string getType() { return type; }

    protected:
        sf::Sprite sprite; 
        sf::Vector2f size;
        std::string type;
};
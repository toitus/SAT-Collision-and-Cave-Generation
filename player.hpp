#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Player : public Entity {
    public:
        Player();
        void update(float dt);
        void draw(sf::RenderWindow* w);

        void move(sf::Vector2f offset) { sprite.move(offset); }
        sf::Vector2f get_position() { return sprite.getPosition(); }
        sf::Vector2f get_center() { return sprite.getPosition() + size/2.f; }
        sf::Vector2f get_size() { return size; }
        std::vector<sf::Vector2f> get_points(sf::Vector2f p);
        void set_position(sf::Vector2f p) { sprite.setPosition(p); }
        
    private:
        bool w, a, s, d;
};
#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Player : public Entity {
    public:
        Player();
        void update(float dt);
        void draw(sf::RenderWindow* w);

        sf::Vector2f get_center() { sprite.getPosition() + size/2.f; }
        sf::Vector2f get_size() { return size; }
        std::vector<sf::Vector2f> get_points();
        std::vector<sf::Vector2f> get_separating_axes();
        void set_position(sf::Vector2f p) { sprite.setPosition(p); }
        bool movement_queued() { return movement_queue.size() > 0; }
        void dequeue_movement() { movement_queue.pop_back(); }
        sf::Vector2f next_move() { return movement_queue.front(); }
        
    private:
        bool w, a, s, d;
        void movement_input();
        void queue_movement(float dt);
        std::vector<sf::Vector2f> movement_queue;
};
#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "entity.hpp"
#include "player.hpp"

class World {
    public:
        void add(Entity* e) { entities.push_back(e); }
        void update(float dt);
        sf::Vector2f get_mtv() { return mtv; }
        bool check_player_collision(std::vector<sf::Vector2f> player);
    private:
        float min(float a, float b);
        float max(float a, float b);
        float dot(sf::Vector2f a, sf::Vector2f b);

        void project_to_axis(std::vector<sf::Vector2f> points, sf::Vector2f axis, float& min, float& max);
        bool update_min_overlap(int axis_index, float a_min, float b_max, int& min_overlap_axis, float& min_overlap);
        

        std::vector<Entity*> entities;
        sf::Vector2f mtv;
};
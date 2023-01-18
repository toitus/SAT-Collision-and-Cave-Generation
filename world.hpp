#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "player.hpp"

class World {
    public:
        void add(Entity* e) { entities.push_back(e); }
        void set_player(Player* p) { player = p; }
        void update(float dt);
    private:
        float min(float a, float b);
        float max(float a, float b);
        float dot(sf::Vector2f a, sf::Vector2f b);

        void project_to_axis(Entity* e, sf::Vector2f axis, float& min, float& max);
        bool update_min_overlap(int axis_index, float a_min, float b_max, int& min_overlap_axis, float& min_overlap);
        bool check_player_collision(Entity* e);


        Player* player;
        std::vector<Entity*> entities;
};
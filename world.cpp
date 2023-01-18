#include "world.hpp"

void World::update(float dt) {
    if (player->movement_queued()) {
        for (int i = 0; i < entities.size(); ++i) {
            if (!check_player_collision(entities[i])) {
                player->set_position(player->next_move());
                player->dequeue_movement();
            }
        }
    }
}

float World::min(float a, float b) {
    if (a == b) return a;
    if (a < b) return a;
    return b;
}

float World::max(float a, float b) {
    if (a == b) return a;
    if (a > b) return a;
    return b;
}

float World::dot(sf::Vector2f a, sf::Vector2f b) {
    return (a.x * b.x) + (a.y * b.y);
}

void World::project_to_axis(Entity* e, sf::Vector2f axis, float& min, float& max) {
    std::vector<sf::Vector2f> points = e->get_points();
    float product = dot(points[0], axis);
    min = product;
    max = product;
    for (int i = 1; i < points.size(); ++i) {
        product = dot(points[i], axis);
        if (product < min) min = product;
        if (product > max) max = product;
    }
}

bool World::update_min_overlap(int axis_index, float a_min, float b_max, int& min_overlap_axis, float& min_overlap) {
    float overlap = b_max - a_min;
    if (overlap < min_overlap) {
        min_overlap = overlap;
        min_overlap_axis = axis_index;
        return true;
    }
    return false;
}

//checks collision between two Entities a, b
bool World::check_player_collision(Entity* e) {
    std::vector<sf::Vector2f> player_axes = player->get_separating_axes();

    float a_min, a_max;
    float b_min, b_max;

    float min_overlap = 999;

    int min_overlap_axis;

    //1 = from a
    //2 = from b
    int origin = 0;

    sf::Vector2f mtv = sf::Vector2f(0, 0);

    for (int i = 0; i < player_axes.size(); ++i) {
        project_to_axis(player, player_axes[i], a_min, a_max);
        project_to_axis(e, player_axes[i], b_min, b_max);
        if (a_max < b_min || b_max < a_min) { return false; }
        if (update_min_overlap(i, a_min, b_max, min_overlap_axis, min_overlap)) { origin = 1; }
    }

    std::vector<sf::Vector2f> entity_axes = e->get_separating_axes();
    for (int j = 0; j < entity_axes.size(); ++j) {
        project_to_axis(player, entity_axes[j], a_min, a_max);
        project_to_axis(e, entity_axes[j], b_min, b_max);
        if (a_max < b_min || b_max < a_min) { return false; }
        if (update_min_overlap(j, a_min, b_max, min_overlap_axis, min_overlap)) { origin = 2; }
    }

    if (origin == 1) {
        mtv.x = min_overlap * player_axes[min_overlap_axis].x;
        mtv.y = min_overlap * player_axes[min_overlap_axis].y;
    }

    if (origin == 2) {
        mtv.x = min_overlap * entity_axes[min_overlap_axis].x;
        mtv.y = min_overlap * entity_axes[min_overlap_axis].y;
    }

    player->set_position(player->next_move()+mtv);

    return true;

}

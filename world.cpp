#include "world.hpp"

void World::update(float dt) {

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

void World::project_to_axis(std::vector<sf::Vector2f> points, sf::Vector2f axis, float& min, float& max) {
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
bool World::check_player_collision(std::vector<sf::Vector2f> player) {

    std::vector<sf::Vector2f> separating_axes = std::vector<sf::Vector2f>{
        sf::Vector2f(0,-1), sf::Vector2f(1, 0), sf::Vector2f(0, 1), sf::Vector2f(-1, 0)
    };

    float a_min, a_max;
    float b_min, b_max;

    float min_overlap = 999;

    int min_overlap_axis;

    mtv = sf::Vector2f(0, 0);

    for (int i = 0; i < separating_axes.size(); ++i) {
        project_to_axis(player, separating_axes[i], a_min, a_max);
        project_to_axis(entities[0]->get_points(sf::Vector2f(0, 0)), separating_axes[i], b_min, b_max);
        if (a_max < b_min || b_max < a_min) { return false; }
        update_min_overlap(i, a_min, b_max, min_overlap_axis, min_overlap);
    }

    mtv.x = min_overlap * separating_axes[min_overlap_axis].x;
    mtv.y = min_overlap * separating_axes[min_overlap_axis].y;

    return true;
}

#include "rectangle.hpp"

Rectangle::Rectangle() {
    if (texture.loadFromFile("content/player.png")) {
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(50, 50));
        size = sf::Vector2f(32.f, 32.f);

        sf::Vector2f position = sprite.getPosition();
        points.push_back(position);
        points.push_back(sf::Vector2f(position.x+size.x, position.y));
        points.push_back(sf::Vector2f(position.x+size.x, position.y+size.y));
        points.push_back(sf::Vector2f(position.x, position.y+size.y));

        float e1x = points[0].x - points[1].x;
        float e1y = points[0].y - points[1].y;

        float e2x = points[1].x - points[2].x;
        float e2y = points[1].y - points[2].y;

        float e3x = points[2].x - points[3].x;
        float e3y = points[2].y - points[3].y;

        float e4x = points[3].x - points[0].x;
        float e4y = points[3].y - points[0].y;

        separating_axes.push_back(normalize(sf::Vector2f(-e1y, e1x)));
        separating_axes.push_back(normalize(sf::Vector2f(-e2y, e2x)));
        separating_axes.push_back(normalize(sf::Vector2f(-e3y, e3x)));
        separating_axes.push_back(normalize(sf::Vector2f(-e4y, e4x)));
    }
}

std::vector<sf::Vector2f> Rectangle::get_points() {
    return points;
}

std::vector<sf::Vector2f> Rectangle::get_separating_axes() {
    return separating_axes;
}

void Rectangle::update(float dt) {

}

void Rectangle::draw(sf::RenderWindow* w) {
    w->draw(sprite);
}
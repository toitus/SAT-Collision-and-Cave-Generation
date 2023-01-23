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
    }
}

std::vector<sf::Vector2f> Rectangle::get_points(sf::Vector2f p) {
    return points;
}

void Rectangle::update(float dt) {

}

void Rectangle::draw(sf::RenderWindow* w) {
    w->draw(sprite);
}
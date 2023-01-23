#include "player.hpp"

Player::Player() {
    if (texture.loadFromFile("content/player.png")) {
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(0, 0));
        size = sf::Vector2f(32.f, 32.f);
    }
}

void Player::update(float dt) {

}

void Player::draw(sf::RenderWindow* w) {
    w->draw(sprite);
}

std::vector<sf::Vector2f> Player::get_points(sf::Vector2f p) {
    
    std::vector<sf::Vector2f> points = std::vector<sf::Vector2f>{
        p, sf::Vector2f(p.x+size.x, p.y), sf::Vector2f(p.x+size.x, p.y+size.y), sf::Vector2f(p.x, p.y+size.y)
    };

    return points;
}
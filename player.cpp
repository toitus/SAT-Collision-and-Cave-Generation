#include "player.hpp"

void Player::update(float dt) {
    movement(dt);
}

void Player::draw(sf::RenderWindow* w) {

}

void Player::movement(float dt) {
    bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    float speed = 250.f * dt;

    if ((w && a) || (w && d) || (s && a) || (s && d)) { speed *= 0.707; } 
}
#include "player.hpp"

Player::Player() {
    if (texture.loadFromFile("content/player.png")) {
        size = sf::Vector2f(texture.getSize().x, texture.getSize().y);
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
        type = "player";
    } else {
        std::cout << "failed to load 'content/player.png'" << std::endl;
    }
}

void Player::update(float dt) {
    movement(dt);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::movement(float dt) {
    bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    float speed = 250.f * dt;

    if ((w && a) || (w && d) || (s && a) || (s && d)) { speed *= 0.725; } 

    speed = std::floor(speed);

    sf::Vector2f offset = sf::Vector2f(0, 0);

    if (w) { offset += sf::Vector2f(0, -speed); }
    if (a) { offset += sf::Vector2f(-speed, 0); }
    if (s) { offset += sf::Vector2f(0, speed); }
    if (d) { offset += sf::Vector2f(speed, 0); }

    sprite.move(offset);
}
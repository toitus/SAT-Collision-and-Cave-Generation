#include "player.hpp"

Player::Player() {
    rectangle.setPosition(sf::Vector2f(0, 0));
    rectangle.setSize(size);
    rectangle.setOutlineThickness(1.f);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::Green);
}

void Player::update(float dt, sf::View* v) {
    movement_input();
    apply_movement(dt);
    v->setCenter(get_center());
}

void Player::draw(sf::RenderWindow* w) {
    w->draw(rectangle);
}

void Player::movement_input() {
    w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::apply_movement(float dt) {
    float speed = 250.f * dt;

    if ((w && a) || (w && d) || (s && a) || (s && d)) {
        speed *= 0.707;
    } 

    if (w) { rectangle.move(0, -speed); }
    
    if (a) { rectangle.move(-speed, 0); }

    if (s) { rectangle.move(0, speed); }

    if (d) { rectangle.move(speed, 0); }
}
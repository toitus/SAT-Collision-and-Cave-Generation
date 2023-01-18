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
    movement_input();
    queue_movement(dt);
}

void Player::draw(sf::RenderWindow* w) {
    w->draw(sprite);
}

std::vector<sf::Vector2f> Player::get_points() {
    sf::Vector2f position = sprite.getPosition();
    points.clear();

    points.push_back(position);
    points.push_back(sf::Vector2f(position.x+size.x, position.y));
    points.push_back(sf::Vector2f(position.x+size.x, position.y+size.y));
    points.push_back(sf::Vector2f(position.x, position.y+size.y));

    return points;
}

std::vector<sf::Vector2f> Player::get_separating_axes() {
    separating_axes.clear();

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

void Player::movement_input() {
    w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::queue_movement(float dt) {
    float speed = 250.f * dt;

    if ((w && a) || (w && d) || (s && a) || (s && d)) {
        speed *= 0.707;
    } 

    sf::Vector2f next = sprite.getPosition();

    if (w) { next.y -= speed; }
    
    if (a) { next.x -= speed;}

    if (s) { next.y += speed; }

    if (d) { next.x += speed; }

    movement_queue.push_back(next);
}
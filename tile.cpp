#include "tile.hpp"

Tile::Tile() {
    if (texture.loadFromFile("content/tile.png")) {
        size = sf::Vector2f(texture.getSize().x, texture.getSize().y);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);
    } else {
        std::cout << "failed to load 'content/tile.png'" << std::endl;
    }
}

void Tile::update(float dt) {

}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
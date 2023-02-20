#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "sprite.hpp"
#include "player.hpp"
#include "tile.hpp"

class World {
    public:
        World();

        void update(float dt, sf::View& view);
        void draw(sf::RenderWindow& window);

    private:

        Player player;
        Tile a;
        Tile b;

        std::vector<Sprite*> entities;

        std::vector<sf::Vector2f> separatingAxes = std::vector<sf::Vector2f> {
            sf::Vector2f(-1, 0), //left collide
            sf::Vector2f(0, 1), //top collide
            sf::Vector2f(1, 0), //right collide
            sf::Vector2f(0, -1) //bottom collide
        };

        void resolveCollisions();
        bool checkCollision(Sprite* a, Sprite* b);

        float dot(sf::Vector2f a, sf::Vector2f b);
};
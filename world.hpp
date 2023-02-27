#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "sprite.hpp"
#include "player.hpp"
#include "tilemap.hpp"
#include "tile.hpp"

class World {
    public:
        World();

        void events(sf::Event& event);
        void update(float dt, sf::View& view);
        void draw(sf::RenderWindow& window);

    private:

        Player player;

        Tilemap map;

        //todo: make a class for pushable boxes that isn't Tile (this was just for testing collisions)
        Tile box;
        Tile boxy;
        Tile boxyy;
        sf::Texture boxtexture;

        std::vector<Sprite*> entities;

        std::vector<sf::Vector2f> separatingAxes = std::vector<sf::Vector2f> {
            sf::Vector2f(-1, 0),
            sf::Vector2f(0, -1),
            sf::Vector2f(1, 0), 
            sf::Vector2f(0, 1) 
        };

        void checkCollisions();
        sf::Vector2f getMTV(Sprite* a, Sprite* b);
        void resolveCollisions(Sprite* s);

        float dot(sf::Vector2f a, sf::Vector2f b);
};
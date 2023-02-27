#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "tile.hpp"

class Tilemap {
    public:
        Tilemap();

        void events(sf::Event& event);
        void draw(sf::RenderWindow& window);

        void generate();
        int rows() { return height; }
        int columns() { return width; }
        int getTilesize() { return tilesize; }

        Tile* getTile(int row, int column) { return &tiles[row][column]; }

        sf::Vector2f getRandomEmptyTilePosition();

    private:

        std::vector<std::vector<Tile>> tiles;

        sf::Texture tilesheet;

        int tilesize = 48;
        int width = 50;
        int height = 50;

        sf::IntRect floor = sf::IntRect(0, 0, tilesize, tilesize-1);
        sf::IntRect wall = sf::IntRect(tilesize, 0, tilesize, tilesize);

        std::vector<std::vector<sf::Vector2i>> caverns;

        std::vector<sf::Vector2i> flood(sf::Vector2i root);
};
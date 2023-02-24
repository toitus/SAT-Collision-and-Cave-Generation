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

    private:

        std::vector<std::vector<Tile>> tiles;

        sf::Texture tilesheet;

        sf::IntRect floor = sf::IntRect(0, 0, 32, 32);
        sf::IntRect wall = sf::IntRect(32, 0, 32, 32);

        int tilesize = 32;
        int width = 60;
        int height = 60;

        std::vector<std::vector<sf::Vector2i>> caverns;

        std::vector<sf::Vector2i> flood(sf::Vector2i root);
};
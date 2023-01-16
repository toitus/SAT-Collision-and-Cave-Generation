#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"

class Game {
    public:
        Game(sf::RenderWindow* w);
        void run();

    private:
        sf::RenderWindow* window;
        sf::Event event;

        Player player;

        sf::View view;
        sf::Vector2f view_size, view_center;

        sf::Clock update_clock;
        sf::Time time_since_last_update = sf::Time::Zero;
        sf::Time target_update_time = sf::seconds(1.f/60.f);

        void events();
        void update();
        void draw();
};
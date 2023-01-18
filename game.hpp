#pragma once

#include <SFML/Graphics.hpp>

#include "world.hpp"
#include "player.hpp"
#include "rectangle.hpp"

class Game {
    public:
        Game(sf::RenderWindow* w);
        void run();

    private:
        sf::RenderWindow* window;
        sf::Event event;

        World world;

        Player player;
        Rectangle rect;

        sf::View view;
        sf::Vector2f view_size, view_center;

        sf::Clock update_clock;
        sf::Time time_since_last_update = sf::Time::Zero;
        sf::Time target_update_time = sf::seconds(1.f/60.f);

        //sf::CircleShape circle;

        void events();
        void update();
        void draw();
};
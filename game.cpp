#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;

    view = sf::View(world.player_center(), sf::Vector2f(window->getSize().x, window->getSize().y));
}

void Game::run() {
    while (window->isOpen()) {
        events();
        time_since_last_update += update_clock.restart();
        while (time_since_last_update >= target_update_time) {
            time_since_last_update -= target_update_time;
            if (window->hasFocus()) {
                update();
            }
        }
        draw();
    }
}

void Game::events() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) { window->close(); }

        if (event.type == sf::Event::Resized) {
            view.setSize(event.size.width, event.size.height);
            window->setView(view);
        }
    }
}

void Game::update() {
    world.update(target_update_time.asSeconds());
    view.setCenter(world.player_center());
}

void Game::draw() {
    window->clear(sf::Color::Black);
        window->setView(view);
        world.draw(window);
    window->display();
}
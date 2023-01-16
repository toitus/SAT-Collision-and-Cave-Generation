#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;

    view_center = player.get_center();
    view_size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(view_center, view_size);
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
    player.update(target_update_time.asSeconds(), &view);
}

void Game::draw() {
    window->clear(sf::Color::Black);
        window->setView(view);
        player.draw(window);
    window->display();
}
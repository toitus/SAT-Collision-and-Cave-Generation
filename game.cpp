#include "game.hpp"

Game::Game() {
    window.create(sf::VideoMode(1280, 720, sf::VideoMode::getDesktopMode().bitsPerPixel), "SAT");
    view = sf::View(sf::Vector2f(16, 16), sf::Vector2f(window.getSize().x, window.getSize().y));
}

void Game::run() {
    while (window.isOpen()) {
        events();
        timeSinceLastUpdate += updateClock.restart();
        while (timeSinceLastUpdate >= targetUpdateTime) {
            timeSinceLastUpdate -= targetUpdateTime;
            if (window.hasFocus()) {
                update();
            }
        }
        draw();
    }
}

void Game::events() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) { window.close(); }

        if (event.type == sf::Event::Resized) {
            view.setSize(event.size.width, event.size.height);
            window.setView(view);
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0 && zoomedOut) { view.zoom(1.f/zoom); zoomedOut = !zoomedOut; } 
            else if (event.mouseWheelScroll.delta < 0 && !zoomedOut) { view.zoom(zoom); zoomedOut = !zoomedOut; }
        }

        world.events(event);
        
    }
}

void Game::update() {
    world.update(targetUpdateTime.asSeconds(), view);
}

void Game::draw() {
    window.clear(sf::Color::Black);
        window.setView(view);
        world.draw(window);
    window.display();
}
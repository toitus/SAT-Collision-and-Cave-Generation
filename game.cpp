#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;

    world.add(&rect);

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
    world.update(target_update_time.asSeconds());
    player_movement();
    player.update(target_update_time.asSeconds());
    view.setCenter(player.get_center());
}

void Game::draw() {
    window->clear(sf::Color::Black);
        window->setView(view);
        rect.draw(window);
        player.draw(window);
    window->display();
}

void Game::player_movement() {
    w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    float speed = 250.f * target_update_time.asSeconds();

    if ((w && a) || (w && d) || (s && a) || (s && d)) {
        speed *= 0.707;
    } 

    sf::Vector2f next = player.get_position();

    if (w) { next.y = -speed; }
    else if (s) { next.y = speed; }
    else { next.y = 0; } 
    
    if (a) { next.x = -speed;}
    else if (d) { next.x = speed; }
    else { next.x = 0; }

    if (world.check_player_collision(player.get_points(player.get_position() + next))) {
        player.move(next + world.get_mtv());
    } else { 
        player.move(next);
    }

}
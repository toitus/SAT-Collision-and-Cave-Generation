#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900, sf::VideoMode::getDesktopMode().bitsPerPixel), "SAT");
    Game game(&window);
    game.run();
    return 0;
}
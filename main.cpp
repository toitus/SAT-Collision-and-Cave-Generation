#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "game.hpp"

int main() {
    std::srand(std::time(nullptr));
    Game game;
    game.run();
    return 0;
}
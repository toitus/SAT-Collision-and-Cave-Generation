#include "tilemap.hpp"

Tilemap::Tilemap() {
    tiles = std::vector<std::vector<Tile>>(height, std::vector<Tile>(width));
    if (tilesheet.loadFromFile("content/tilesheet.png")) {
        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                tiles[row][column].setTexture(&tilesheet);
                tiles[row][column].setSize(sf::Vector2f(tilesize, tilesize));
                tiles[row][column].position(sf::Vector2f(column*tilesize, row*tilesize));
            }
        }
    }
}

void Tilemap::draw(sf::RenderWindow& window) {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            tiles[row][column].draw(window);
        }
    }
}

void Tilemap::generate() {
    std::vector<std::vector<int>> current(height, std::vector<int>(width, 1));
    std::vector<std::vector<int>> old(height, std::vector<int>(width, 1));

    caverns.clear();

    for (int row = 1; row < height-1; ++row) {
        for (int column = 1; column < width-1; ++column) {
            if ((std::rand() % 100) < 43) {
                current[row][column] = 0;
            }
        }
    }

    for (int step = 0; step < 5; ++step) {
        old = current;
        for (int row = 1; row < height-1; ++row) {
            for (int column = 1; column < width-1; ++column) {
                int count = old[row-1][column] + old[row+1][column] + 
                            old[row][column-1] + old[row][column+1] +
                            old[row-1][column-1] + old[row+1][column+1] + 
                            old[row-1][column+1] + old[row+1][column-1];
                
                if (count > 4) {
                    current[row][column] = 0;
                } else {
                    current[row][column] = 1;
                }
            }
        }
    }

    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (current[row][column] == 0) {
                tiles[row][column].setTextureRect(floor);
                tiles[row][column].setType("walkable");
                tiles[row][column].cavern = 0;
            } else if (current[row][column] == 1) {
                tiles[row][column].setTextureRect(wall);
                tiles[row][column].setType("static");
                tiles[row][column].cavern = -1;
                if (row == 0 || row == height-1 || column == 0 || column == width-1) {
                    tiles[row][column].removable = false;
                }
            }
        }
    }

    for (int row = 1; row < height-1; ++row) {
        for (int column = 1; column < width-1; ++column) {
            if (tiles[row][column].cavern == 0) {
                caverns.push_back(flood(sf::Vector2i(row, column)));
            }
        }
    }

}

std::vector<sf::Vector2i> Tilemap::flood(sf::Vector2i root) {
    std::vector<sf::Vector2i> queue;
    std::vector<sf::Vector2i> cavern;
    queue.push_back(root);
    while (queue.size() > 0) {
        sf::Vector2i temp = queue.front();
        queue.erase(queue.begin());
        if (tiles[temp.x][temp.y].cavern == 0) {
            tiles[temp.x][temp.y].cavern = caverns.size() + 1;
            cavern.push_back(temp);
            if (tiles[temp.x-1][temp.y].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y)); }
            if (tiles[temp.x+1][temp.y].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y)); }
            if (tiles[temp.x][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y-1)); }
            if (tiles[temp.x][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y+1)); }
            if (tiles[temp.x-1][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y-1)); }
            if (tiles[temp.x+1][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y+1)); }
            if (tiles[temp.x+1][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y-1)); }
            if (tiles[temp.x-1][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y+1)); }
        }
    }
    return cavern;
}

sf::Vector2f Tilemap::getRandomEmptyTilePosition() {
    int largest = 0;
    for (int i = 1; i < caverns.size(); ++i) {
        if (caverns[i].size() > caverns[largest].size()) {
            largest = i;
        }
    }
    int tile = std::rand() % caverns[largest].size();
    return sf::Vector2f(caverns[largest][tile].y*tilesize, caverns[largest][tile].x*tilesize);
}
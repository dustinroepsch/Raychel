#include "game.h"

#include <iostream>

Game::Game() {
    sf::Image levelImage;
    if (!levelImage.loadFromFile("resources/BasicLevel.png")) {
        std::cerr << "Unabled To load level" << std::endl;
    }
    currentLevel = std::make_shared<Level>(levelImage, simpleTileMap);
}

void Game::printCurrentLevelAsAscii() {
    currentLevel->printAsAscii();
}
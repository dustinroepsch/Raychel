#include "level.h"

#include <iostream>

Level::Level(const sf::Image &image, const TileMap &tileMap) : dimensions(image.getSize()) {
    tiles = new std::shared_ptr<LevelTile>[dimensions.x * dimensions.y];

    for (int row = 0; row < dimensions.y; row++) {
        for (int col = 0; col < dimensions.x; col++) {
            tiles[row * dimensions.x + col] = tileMap.colorToTile(image.getPixel(col, row));
        }
    }
}

Level::~Level() {
    delete[] tiles;
}

void Level::printAsAscii() {
    for (int row = 0; row < dimensions.y; row++) {
        for (int col = 0; col < dimensions.x; col++) {
            std::cout << tiles[row * dimensions.x + col]->getAsciiRepresentation();
        }
        std::cout << std::endl;
    }
}
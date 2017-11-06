#include "level.h"

Level::Level(const sf::Image &image, const TileMap &tileMap) : dimensions(image.getSize()) {
    tiles = new LevelTile[dimensions.x * dimensions.y];

    for (int row = 0; row < dimensions.y; row++) {
        for (int col = 0; col < dimensions.x; col++) {
            tiles[row * dimensions.x + col] = tileMap.colorToTile(image.getPixel(col, row));
        }
    }
}

Level::~Level() {
    delete[] tiles;
}
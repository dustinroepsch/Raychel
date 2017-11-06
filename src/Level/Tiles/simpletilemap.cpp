#include "simpletilemap.h"

const std::shared_ptr<LevelTile> SimpleTileMap::colorToTile(const sf::Color &color) const {
    if (color == sf::Color::Black) {
        return wall;
    } else {
        return floor;
    }
}

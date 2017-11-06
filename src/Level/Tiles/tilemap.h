#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "leveltile.h"

class TileMap {
public:
    virtual const LevelTile& colorToTile(const sf::Color &color) const = 0;
};

#endif
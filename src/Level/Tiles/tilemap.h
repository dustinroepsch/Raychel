#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "leveltile.h"

class TileMap {
public:
    virtual  const std::shared_ptr<LevelTile> colorToTile(const sf::Color &color) const = 0;
};

#endif
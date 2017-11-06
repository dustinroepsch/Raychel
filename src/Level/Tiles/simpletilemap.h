#ifndef SIMPLETILEMAP_H
#define SIMPLETILEMAP_H

#include "tilemap.h"
#include "floortile.h"
#include "walltile.h"

class SimpleTileMap : public TileMap {
public:
    const LevelTile& colorToTile(const sf::Color &color) const override;
private:
    const FloorTile floor;
    const WallTile wall;
};

#endif
#ifndef SIMPLETILEMAP_H
#define SIMPLETILEMAP_H

#include "tilemap.h"
#include "floortile.h"
#include "walltile.h"

class SimpleTileMap : public TileMap
{
  public:
    SimpleTileMap()
    {
        floor = std::make_shared<FloorTile>();
        wall = std::make_shared<WallTile>();
    };
    const std::shared_ptr<LevelTile> colorToTile(const sf::Color &color) const override;

  private:
    std::shared_ptr<FloorTile> floor;
    std::shared_ptr<WallTile> wall;
};

#endif
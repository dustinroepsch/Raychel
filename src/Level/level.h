#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameObjects/gameobject.h"
#include "Tiles/leveltile.h"
#include "Tiles/tilemap.h"

class Level
{
public:
    Level(const sf::Image &image, const TileMap &tileMap);
    ~Level();
private:
    const sf::Vector2u dimensions;
    LevelTile* tiles;
    std::vector<GameObject> gameObjects;
};

#endif
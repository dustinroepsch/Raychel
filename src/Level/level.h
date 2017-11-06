#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameObjects/gameobject.h"
#include "Tiles/leveltile.h"
#include "Tiles/tilemap.h"

class Level
{
public:
    Level(const sf::Image &image, const TileMap &tileMap);
    ~Level();

    void printAsAscii();
private:
    const sf::Vector2u dimensions;
    std::shared_ptr<LevelTile>* tiles;
    std::vector<GameObject> gameObjects;
};

#endif
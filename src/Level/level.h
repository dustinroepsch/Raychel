#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../castresult.h"
#include "../player.h"
#include "GameObjects/gameobject.h"
#include "Tiles/leveltile.h"
#include "Tiles/tilemap.h"

class Level
{
public:
    Level(const sf::Image &image, const TileMap &tileMap);
    ~Level();

    void printAsAscii();
    CastResult rayCast(const Player &player, float castAngle) const;
    
private:
    float getX(float slope, float y, const sf::Vector2f &point) const;    
    float getY(float slope, float x, const sf::Vector2f &point) const;
    bool checkCollision(const sf::Vector2f &posToCheck, float castSlope, int xDirection) const;
    int tileIndex(int row, int col) const;

    const sf::Vector2u dimensions;
    std::shared_ptr<LevelTile>* tiles;
    std::vector<GameObject> gameObjects;
};

#endif
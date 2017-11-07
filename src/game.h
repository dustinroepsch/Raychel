#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Level/level.h"
#include "player.h"
#include "Level/Tiles/simpletilemap.h"

class Game
{
  public:
    Game();

    void printCurrentLevelAsAscii();
    void render(sf::Uint8 *pixels);
    Player player;
    const std::string getDebugText();
  private:
    std::shared_ptr<Level> currentLevel;
    const SimpleTileMap simpleTileMap;
};

#endif
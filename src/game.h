#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include "Level/level.h"
#include "player.h"
#include "Level/Tiles/simpletilemap.h"

class Game {
public:
    Game();

    void printCurrentLevelAsAscii();
private:
    std::shared_ptr<Level> currentLevel;
    const SimpleTileMap simpleTileMap;
    //Player player;
};

#endif
#ifndef WALLTILE_H
#define WALLTILE_H

#include "leveltile.h"

class WallTile : public LevelTile {
public:
    WallTile(){};
    inline char getAsciiRepresentation() const override {
        return '#';
    }
    inline bool isOpaque() const override {
        return true;
    }
};

#endif

#ifndef FLOORTILE_H
#define FLOORTILE_H

#include "leveltile.h"

class FloorTile : public LevelTile {
public:
    FloorTile(){};
    inline char getAsciiRepresentation() const override {
        return ' ';
    }
    inline bool isOpaque() const override {
        return false;
    }
};

#endif
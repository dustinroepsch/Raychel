#ifndef LEVELTILE_H
#define LEVELTILE_H

class LevelTile {
public:
    virtual char getAsciiRepresentation() const = 0;
    virtual bool isOpaque() const = 0;
};
#endif
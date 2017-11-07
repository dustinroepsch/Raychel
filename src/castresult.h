#ifndef CASTRESULT_H
#define CASTRESULT_H

class CastResult {
public:
    CastResult(int distance, bool horizontalHit) : distance(distance), horizontalHit(horizontalHit) {};
    const int distance;
    const bool horizontalHit;
};

#endif
#ifndef CASTRESULT_H
#define CASTRESULT_H

class CastResult {
public:
    CastResult(float distance, bool horizontalHit) : distance(distance), horizontalHit(horizontalHit) {};
    const float distance;
    const bool horizontalHit;
};

#endif
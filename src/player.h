#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y, float angle) : angle(angle), position(x, y) {};
    float angle;
    sf::Vector2f position;
};

#endif
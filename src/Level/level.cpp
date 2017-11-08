#include "level.h"

#include <iostream>
#include <cmath>

Level::Level(const sf::Image &image, const TileMap &tileMap) : dimensions(image.getSize())
{
    tiles = new std::shared_ptr<LevelTile>[dimensions.x * dimensions.y];

    for (int row = 0; row < dimensions.y; row++)
    {
        for (int col = 0; col < dimensions.x; col++)
        {
            tiles[tileIndex(row, col)] = tileMap.colorToTile(image.getPixel(col, row));
        }
    }
}

Level::~Level()
{
    delete[] tiles;
}

void Level::printAsAscii()
{
    for (int row = 0; row < dimensions.y; row++)
    {
        for (int col = 0; col < dimensions.x; col++)
        {
            std::cout << tiles[tileIndex(row, col)]->getAsciiRepresentation();
        }
        std::cout << std::endl;
    }
}
float Level::getY(float slope, float x, const sf::Vector2f &point) const
{
    //y - y1 = m (x - x1)
    return slope * (x - point.x) + point.y;
}

float Level::getX(float slope, float y, const sf::Vector2f &point) const
{
    //y - y1 = m(x - x1)
    //y - y1 = mx - mx1
    //(y - y1) / m = x - x1
    //(y - y1) / m + x1 = x
    return (y - point.y) / slope + point.x;
}

int Level::tileIndex(int row, int col) const
{
    return row * dimensions.x + col;
}

bool Level::checkCollision(const sf::Vector2f &posToCheck, float castAngle, int xDirection) const
{

    //truncate to floor towards zero
    int col = posToCheck.x ;//+ cos(castAngle) * .0001;
    int row = posToCheck.y ;//+ sin(castAngle) * .0001;;

    if (col < 0 || col >= dimensions.x || row < 0 || row >= dimensions.y)
    {
        //always collide out of bounds;
        std::cout << "This shouldn't happen" << std::endl;
        return true;
    }

    return tiles[tileIndex(row, col)]->isOpaque();
}

float getPerpDistance(const sf::Vector2f &pos, const Player &player)
{
    sf::Vector2f distance = pos - player.position;

    sf::Vector2f playerDirection(cos(player.angle), sin(player.angle));

    //project our distance vector onto the direction the player is facing
    //distance dot playerDirection / |playerDirection|^2

    return (distance.x * playerDirection.x + distance.y * playerDirection.y) / (playerDirection.x * playerDirection.x + playerDirection.y * playerDirection.y);
}
float dist(const sf::Vector2f &a, const sf::Vector2f &b)
{
    sf::Vector2f distVec(a.x - b.x, a.y - b.y);
    return sqrt(distVec.x * distVec.x + distVec.y * distVec.y);
}

CastResult Level::rayCast(const Player &player, float castAngle) const
{

    const sf::Vector2f startingPosition = player.position;

    if (castAngle < 0)
    {
        castAngle += 3.1415926 * 2;
    }
    if (castAngle > 3.1415926 * 2)
    {
        castAngle -= 3.1415926 * 2;
    }
    bool horizontalCollision = false;

    sf::Vector2f currentPosition = startingPosition;

    //negate the slope because y increases as the player moves down, not up
    const float castSlope = tanf(castAngle);
    //todo special case when casting straight up or down.
    const int xDirection = cos(castAngle) < 0 ? -1 : 1;
    //negate y for the usual reason
    const int yDirection = sin(castAngle) < 0 ? -1 : 1;

    //use these to check if we are hitting a wall horizontally or vertically atm,
    //and also to find the next cell we need to check
    sf::Vector2f nextPositionAlongX;
    sf::Vector2f nextPositionAlongY;

    //truncate x to floor towards zero
    nextPositionAlongX.x = (int)(currentPosition.x + xDirection); //snap ourselves to a grid line
    nextPositionAlongX.y = getY(castSlope, nextPositionAlongX.x, startingPosition);

    nextPositionAlongY.y = (int)(currentPosition.y + yDirection);
    nextPositionAlongY.x = getX(castSlope, nextPositionAlongY.y, startingPosition);

    if (dist(nextPositionAlongX, startingPosition) < dist(nextPositionAlongY, startingPosition))
    {
        currentPosition = nextPositionAlongX;
        horizontalCollision = false;
    }
    else
    {
        currentPosition = nextPositionAlongY;
        horizontalCollision = true;
    }

    while (!checkCollision(currentPosition, castAngle, xDirection))
    {
        //truncate x to floor towards zero
        nextPositionAlongX.x = (int)(currentPosition.x + xDirection); //snap ourselves to a grid line
        nextPositionAlongX.y = getY(castSlope, nextPositionAlongX.x, startingPosition);

        nextPositionAlongY.y = (int)(currentPosition.y + yDirection);
        nextPositionAlongY.x = getX(castSlope, nextPositionAlongY.y, startingPosition);

        if (dist(nextPositionAlongX, startingPosition) < dist(nextPositionAlongY, startingPosition))
        {
            currentPosition = nextPositionAlongX;
            horizontalCollision = false;
        }
        else
        {
            currentPosition = nextPositionAlongY;
            horizontalCollision = true;
        }
    }

    // return CastResult(dist(currentPosition, startingPosition), horizontalCollision);
     return CastResult(getPerpDistance(currentPosition, player), horizontalCollision);
}

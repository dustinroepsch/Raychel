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

bool Level::checkCollision(const sf::Vector2f &posToCheck, float castSlope, int xDirection) const
{

    //add a small value to our position to get off of the grid lines
    //and ensure that we are rounding to the correct cell
    //truncate to floor towards zero
    int col = (int)(posToCheck.x + .001 * xDirection);
    int row = (int)getY(castSlope, col, posToCheck);

    if (col < 0 || col >= dimensions.x || row < 0 || row >= dimensions.y)
    {
        //always collide out of bounds;
        return true;
    }


    return tiles[tileIndex(row, col)]->isOpaque();
}

float getPerpDistance(const sf::Vector2f &pos, const Player &player)
{
    //we don't have to worry that our y position is weird because the projection will
    //be the same

    double pi = 3.1415926535897;
    float cameraPlaneAngle = player.angle + pi / 2;

    float cameraPlaneX = cos(cameraPlaneAngle);
    float cameraPlaneY = sin(cameraPlaneAngle);
    

    float displacementX = pos.x - player.position.x;
    float displacementY = pos.y - player.position.y;

    //project displacement onto camera plane
    //a dot b / (mag(b) ^2)
    float projectionScaler = (cameraPlaneX * displacementX + cameraPlaneY * displacementY) / (cameraPlaneX * cameraPlaneX + cameraPlaneY * cameraPlaneY);

    return fabs(projectionScaler);
}
float dist(const sf::Vector2f &a, const sf::Vector2f &b) {
    sf::Vector2f distVec(a.x - b.x, a.y - b.y);
    return sqrt(distVec.x * distVec.x + distVec.y * distVec.y);
}

CastResult Level::rayCast(const Player &player, const float angle) const
{

    const sf::Vector2f startingPosition = player.position;
    float castAngle = player.angle + angle;
    if (castAngle < 0) {
        castAngle += 3.1415926 * 2;
    }
    if (castAngle > 3.1415926 * 2) {
        castAngle -= 3.1415926 * 2;
    }
    bool horizontalCollision = false;

    sf::Vector2f currentPosition = startingPosition;

    //negate the slope because y increases as the player moves down, not up
    const float castSlope = -tanf(castAngle);
    //todo special case when casting straight up or down.
    const int xDirection = cos(castAngle) < 0 ? -1 : 1;
    //negate y for the usual reason
    const int yDirection = sin(castAngle) < 0 ? 1 : -1;

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

        if (dist(nextPositionAlongX, startingPosition) < dist(nextPositionAlongY, startingPosition) )
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
    
    return CastResult(dist(currentPosition, startingPosition), horizontalCollision);
    //return CastResult(getPerpDistance(currentPosition, player), horizontalCollision);
}

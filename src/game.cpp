#include "game.h"

#include <iostream>
#include <cmath>

#include "config.h"

Game::Game() : player(2, 3, 0)
{
    sf::Image levelImage;
    if (!levelImage.loadFromFile("resources/BasicLevel.png"))
    {
        std::cerr << "Unabled To load level" << std::endl;
    }
    currentLevel = std::make_shared<Level>(levelImage, simpleTileMap);
}

void Game::printCurrentLevelAsAscii()
{
    std::cout << "printing level" << std::endl;
    currentLevel->printAsAscii();
}

float scale(float x, float xStart, float xEnd, float newStart, float newEnd) {
    //We have two points (xStart, newStart) and (xEnd, newEnd)
    float slope = (newEnd - newStart) / (xEnd - xStart);
    //y - y1 = m (X - x1)
    return slope * (x - xStart) + newStart;
}

void Game::render(sf::Uint8 *pixels)
{
    //temporary, eventually use textures
    sf::Color skyColor(0, 0, 255);
    sf::Color wallColorHoriz(0, 255, 0);
    sf::Color wallColorVer(0, 200, 0);
    sf::Color floorColor(20, 20, 20);


    float castAngle = player.angle - Config::playerFov / 2;
    const float deltaAngle = Config::playerFov / Config::windowWidth;

    for (int col = 0; col < Config::windowWidth; col++, castAngle += deltaAngle)
    {
        CastResult castResult = currentLevel->rayCast(player, castAngle);
        
        int wallHeight = scale(castResult.distance, 0, 1, Config::windowHeight, Config::windowHeight / 2);
        if (wallHeight > Config::windowHeight) {
            wallHeight = Config::windowHeight;
        }

     
    
        for (int row = 0; row < Config::windowHeight; row++) {
            float center = Config::windowHeight / 2;
            sf::Color pixelColor;

            if (fabs(row - center) < wallHeight / 2.0) {
                pixelColor = castResult.horizontalHit ? wallColorHoriz : wallColorVer;
            } else if (row < center) {
                pixelColor = floorColor;
            } else {
                pixelColor = skyColor;
            }

            int pixelStart = (row * Config::windowWidth + col) * 4;
            pixels[pixelStart] = pixelColor.r;
            pixels[pixelStart + 1] = pixelColor.g;
            pixels[pixelStart + 2] = pixelColor.b;
            pixels[pixelStart + 3] = pixelColor.a;
        
        }

    }

   

}
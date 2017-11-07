#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "config.h"
#include "game.h"

int main()
{
    Game game;

    game.printCurrentLevelAsAscii();

    sf::RenderWindow gameWindow(sf::VideoMode(Config::windowWidth, Config::windowHeight), "Raychel");
    sf::Texture texture;
    texture.create(Config::windowWidth, Config::windowHeight);
    sf::Sprite sprite(texture);
    sf::Uint8 *pixels = new sf::Uint8[Config::windowWidth * Config::windowHeight * 4];

    sf::Text debugText;
    sf::Font font;
    if (!font.loadFromFile("resources/PT_Sans-Web-Regular.ttf")) {
        std::cout << "Error loading debug font" << std::endl;
    }
    
    debugText.setFillColor(sf::Color::Red);
    debugText.setCharacterSize(70);
    debugText.setFont(font);

    while (gameWindow.isOpen())
    {
        sf::Event Event;
        while (gameWindow.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                gameWindow.close();
            else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Left) {
                    game.player.angle -= .1;
                }
                if (Event.key.code == sf::Keyboard::Right) {
                    game.player.angle += .1;
                }
                if (Event.key.code == sf::Keyboard::Up) {
                    game.player.position.x += cos(game.player.angle) * .1;
                    game.player.position.y -= sin(game.player.angle) * .1;
                }
            }
        }

        debugText.setString(game.getDebugText());

        game.render(pixels);
        texture.update(pixels);
        gameWindow.draw(sprite);
        gameWindow.draw(debugText);
        gameWindow.display();
    }

    delete[] pixels;
    return 0;
}
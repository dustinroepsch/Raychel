#include <SFML/Graphics.hpp>
#include <cstdlib>

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
            }
        }

        game.render(pixels);

        texture.update(pixels);
        gameWindow.draw(sprite);
        gameWindow.display();
    }

    delete[] pixels;
    return 0;
}
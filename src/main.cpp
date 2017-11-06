#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "config.h"
#include "game.h"

int main() {
    Game game;

    game.printCurrentLevelAsAscii();

    sf::RenderWindow gameWindow(sf::VideoMode(Config::windowWidth, Config::windowHeight), "Raychel");
    sf::Texture texture;
    texture.create(Config::windowWidth, Config::windowHeight);
    sf::Sprite sprite(texture);
    sf::Uint8* pixels = new sf::Uint8[Config::windowWidth * Config::windowHeight * 4];

    while (gameWindow.isOpen()) {
        sf::Event Event;
        while (gameWindow.pollEvent(Event)) {
          if (Event.type == sf::Event::Closed)
        gameWindow.close();
        }
        
        for (int i = 0; i < Config::windowHeight * Config::windowWidth * 4; i++) {
            pixels[i] = rand();
        }

        texture.update(pixels);
        gameWindow.draw(sprite);
        gameWindow.display();
      }

      delete[] pixels;
    return 0;
}
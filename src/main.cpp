#include <SFML/Graphics.hpp>

int main() {
    sf::Window App(sf::VideoMode(800, 600), "Raychel");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
          if (Event.type == sf::Event::Closed)
        App.close();
        }
        App.display();
      }
    return 0;
}
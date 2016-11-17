#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 480), "STP Example");
    tmx::MapLoader ml("../maps/");
    ml.Load("example_map.tmx");

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the map
        window.draw(ml);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

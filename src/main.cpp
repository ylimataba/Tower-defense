#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    map::Map map("map_1.tmx");

    Window window("Tower Defence", &map);
    
    //Game game;
    // These should be in the game class
    sf::Clock GameClock;
    sf::Time delayTime = sf::milliseconds(50);
    bool isBuildPhase = true;
    bool isGamePhase = false;

    // Perhaps a rendering thread?!

    //startGameClock();

    while (isBuildPhase && window.isOpen())
    {
        window.checkEvents();
        
        window.clear();

        window.drawAll();

        window.display();

        sf::sleep(delayTime);

        while (isGamePhase && window.isOpen())
        {
            //window.checkEvents();

            //window.drawAll();

            //window.display();

            //sleep
        }
    }

    return EXIT_SUCCESS;
}

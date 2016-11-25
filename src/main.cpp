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
    sf::Time delayTime = sf::milliseconds(50); // This should be done with the fps

    bool isBuildPhase = true;
    bool isGamePhase = false;

    //startGameClock

    while (isBuildPhase && window.isOpen())
    {
        window.checkEvents();

        window.updateTowerPlacer();
        


        window.clear();
        window.drawAll();
        window.display();

        sf::sleep(delayTime);

        while (isGamePhase && window.isOpen())
        {
            //window.checkEvents();

            //window.drawAll();

            //window.display();

            //sf::sleep(delayTime);
        }
    }

    return EXIT_SUCCESS;
}

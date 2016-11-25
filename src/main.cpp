#include "game.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    map::Map map("map_1.tmx");
    Game::Game game(&map);

    Window window("Tower Defence", &map);
    
    //Game game;
    // These should be in the game class
    sf::Clock GameClock;

    sf::Time delayTime = sf::milliseconds(1000 / 60); // This should be done with the fps

    bool isBuildPhase = true;
    bool isGamePhase = true;

    //startGameClock

    while (isBuildPhase && window.isOpen())
    {
        window.checkEvents();

        window.updateTowerPlacer();
        
        window.clear();
        
        window.drawAll();

        if (isGamePhase && window.isOpen())
        {
            //window.checkEvents();

            game.create_enemies(5, .5f);
            game.move_enemies(); 

            //window.drawAll();

            window.draw(game); 
        
            //window.display();

            //sf::sleep(delayTime);
        }

        window.display();

        sf::sleep(delayTime);
    }

    return EXIT_SUCCESS;
}

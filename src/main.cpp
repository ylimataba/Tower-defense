#include "enemy.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    map::Map map("map_1.tmx");
    Enemy::Enemy enemy(0.1f, 1, 1, map.getEnemyRoute()); // just to demo enemy move

    Window window("Tower Defence", &map);
    
    //Game game;
    // These should be in the game class
    sf::Clock GameClock;

    sf::Time delayTime = sf::milliseconds(1000 / 60); // This should be done with the fps

    bool isBuildPhase = true;
    bool isGamePhase = false;

    //startGameClock

    while (isBuildPhase && window.isOpen())
    {
        window.checkEvents();

        window.updateTowerPlacer();
        
        window.clear();

        float deltaTime = GameClock.restart().asSeconds();// just to demo enemy move
        enemy.move(deltaTime);// just to demo enemy move

        window.drawAll();

        window.draw(enemy); // just to demo enemy move

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

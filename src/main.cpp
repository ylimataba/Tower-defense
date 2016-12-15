#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
    bool windowIsOpen = true;

    Game game;

    game.loadRoundsFromFile();

    Window window("Towerdefense", &game);
    while (window.isOpen())
    {
        window.checkEvents();

        if (game.getIsBuildPhase())
        {
            window.updateTowerPlacer();
        }
        else
        {
            game.play();
        }
        
        window.drawAll();
        window.display();

        sf::sleep(game.getDelayTime());

    }

    return EXIT_SUCCESS;
}

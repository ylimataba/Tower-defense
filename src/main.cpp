#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
    bool windowIsOpen = true;
    bool loadPreviousGame = false;

    while (windowIsOpen)
    {
        bool newGame = false;

        map::Map map("map_1.tmx");
        
        Game game(&map);

    	game.loadRoundsFromFile();
        Window window("Tower Defence", &map, &game);

        if (loadPreviousGame)
        {
            game.loadObjects();
        }

        while (!newGame)
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

            if (game.getIsGameOver())
            {
                newGame = true;
            }

            if (game.getLoadGame())
            {
                loadPreviousGame = true;
            }

            if (game.getCloseWindow())
            {
                window.close();
                windowIsOpen = false;
            }
        }
    }

    return EXIT_SUCCESS;
}

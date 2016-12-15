#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include "save.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
    bool windowIsOpen = true;
    bool loadPreviousGame = false;
    std::string nextMap = "map_1.tmx";

    while (windowIsOpen)
    {
        bool newGame = false;

        std::cout << "New game\n";

        map::Map map(nextMap);
        
        Game game(&map);

    	game.loadRoundsFromFile();

        Window window("Tower Defence", &map, &game);

        if (loadPreviousGame)
        {
            std::cout << "Load previous game\n";

            save::Load *newLoad = new save::Load(game.getObjectsToLoad());

            if (!newLoad->gameSaveExists())
            {
                std::cout << "Game save not fount\n";
            }
            else
            {
                game.loadObjects();
            }

            delete newLoad;

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

            nextMap = game.getNextMap();

            if (game.getNewGame())
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
                newGame = true;
                windowIsOpen = false;
            }
        }
    }

    return EXIT_SUCCESS;
}

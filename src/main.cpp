#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    map::Map map("map_1.tmx");

    Game game(&map);

    Window window("Tower Defence", &map, &game);

    game.setBuildPhase(true);

    while (window.isOpen())
    {
        window.checkEvents();

        if (game.getBuildPhase())
        {
            window.updateTowerPlacer();
        }
        else
        {
            game.create_enemies(15, .5f);

            game.move_enemies(); 
        }

        window.drawAll();

        window.display();

        sf::sleep(game.getDelayTime());
    }

    return EXIT_SUCCESS;
}

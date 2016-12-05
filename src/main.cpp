#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    map::Map map("map_1.tmx");
    
    Game game(&map);

    // DELETE THIS FROM MAIN WHEN WAWES ARE READ FROM A FILE
    //example vector to be passed to create_enemies function
    std::vector<char> enemies = {'A','A','A','A','B','B','B','B','C','C','C','C'};

    Window window("Tower Defence", &map, &game);

    while (window.isOpen())
    {
        window.checkEvents();

        if (game.getIsBuildPhase())
        {
            window.updateTowerPlacer();
        }
        else
        {
            // TODO Saisko nämä yhteen funktioon
            game.create_enemies(enemies, .5f);
            game.move_enemies(); 
            game.shoot_enemies();
        }

        window.drawAll();

        window.display();

        sf::sleep(game.getDelayTime());
    }

    return EXIT_SUCCESS;
}

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
    std::string enemies = "AAAAtBBBBtttCCCC";
    std::vector<std::string> rounds;
    rounds.push_back(enemies);
    rounds.push_back(enemies);
    game.set_rounds(rounds);

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
            game.play();
        }
        
        window.drawAll();

        window.display();

        sf::sleep(game.getDelayTime());
    }

    return EXIT_SUCCESS;
}

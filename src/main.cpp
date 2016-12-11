#include "game.hpp"
#include "map.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
    map::Map map("map_1.tmx");
    
    Game game(&map);

    // DELETE THIS FROM MAIN WHEN WAWES ARE READ FROM A FILE
    //example vector to be passed to create_enemies function
    /*
    std::string enemies = "AAAAtBBBBtttCCCC";
    std::vector<std::string> rounds;
    rounds.push_back(enemies);
    rounds.push_back(enemies);
    */
/*
    std::ifstream r_file;
    r_file.open("../maps/rounds.txt");//tiedoston voi toki laittaa muuallekin kuin "maps" -kansioon, kunhan polkua muutetaan
    std::string round;
    std::vector<std::string> rounds;

    while(!((r_file.eof()) or (r_file.fail()))) {
        std::getline(r_file, round);
        rounds.push_back(round);
    }
    r_file.close();
    
    game.set_rounds(rounds);
*/
	game.loadRoundsFromFile();
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
			if(game.health_ok())
            {
	            game.play();
            }
        }
        
        window.drawAll();

        window.display();

        sf::sleep(game.getDelayTime());
    }

    return EXIT_SUCCESS;
}

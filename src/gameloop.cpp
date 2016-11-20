#include <iostream>
#include <vector>
#include "game.hpp"


int main()
{

    Game g = new Game();


    while(g.getRound() < g.rounds && g.health_ok()) //round loop
    {
        g.build();    //build and upgrade towers, create tower buttons in gui
        while(1)    //defense loop
        {
            g.create_enemies();
            move_enemies();

            if(!g.health_ok())
            {
                std::cout << "Game over! Too many enemies achieved the goal." << std::endl;
                break;
            }
            shoot_enemies();

            if(g.round_completed())
            {
                std::cout << "Congratulations! Round " << g.current_round << ". is completed." << std::endl;
                break;
            }
        }

    }

}




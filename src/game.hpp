#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "enemy.hpp"
#include "tower.hpp"

class Game
{
public:
    Game();
    void create_enemies(int current_round, int current_wave);
    void addEnemy(Enemy newEnemy);
    void addTower(Tower newTower);
    void removeEnemy(iterator it);
    void removeTower(iterator it);
    void move_enemies();
    void shoot_enemies();
    bool round_completed();
private:
    int rounds; //number of game rounds
    int waves;  //number of waves in a round
    int current_round;
    int current_wave;
    std::vector<Enemy> enemyList;
    std::vector<Tower> towerList;



};

#endif // GAME_H

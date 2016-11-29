#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "enemy.hpp"
//#include "tower.hpp"
#include "map.hpp"

class Game : public sf::Drawable
{

public:
    Game(map::Map* map);
    ~Game();
    void build();
    void create_enemies(int numberOfEnemies, float timeBetweenSpawn);
    //void addTower(Tower newTower);
    void removeEnemy(std::vector< std::unique_ptr<Enemy> >::iterator it);
    //void removeTower(iterator it);
    void move_enemies();
    //void shoot_enemies();
    bool round_completed();
    //bool health_ok();
    //int getHealth();
    //int getMoney();
    //int getRound();
    //int getWave();

    void setIsBuildPhase(bool setPhase);
    bool getIsBuildPhase();

    void setIsGamePaused(bool pauseState);
    bool getIsGamePaused();

    sf::Time getDelayTime();

private:
    /*
    int rounds; //number of game rounds
    int waves;  //number of waves in a round
    int current_round;
    int current_wave;
    int health;
    int money;
    */
    sf::Clock gameTime;
    const sf::Time delayTime;
    sf::Clock spawnTime;
    sf::Clock moveTime;
    sf::Clock pauseClock;
    float pauseTime = 0;
    int enemies = 0;
    std::vector< std::unique_ptr<Enemy> > enemyList;
    //std::vector<Tower*> towerList;
    map::Map* map;
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    bool isBuildPhase;
    bool isGamePaused;
};

#endif // GAME_H

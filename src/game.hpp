#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "enemy.hpp"
#include "Towers.hpp"
#include "map.hpp"

class Game : public sf::Drawable
{

public:
    Game(map::Map* map);
    ~Game();
    void build();
    void create_enemies(std::vector<char>& listOfEnemies, float timeBetweenSpawn);
    void removeEnemy(std::vector< std::unique_ptr<Enemy> >::iterator it);
    void addTower(sf::Vector2f position, int type);
    void removeEnemy(std::vector<Enemy*>::iterator it);
    void removeTower(std::vector<Tower*>::iterator it);
    void move_enemies();
    void shoot_enemies();
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
    void setSpeed(int speedFactor);
    int getSpeed() const;
    
    friend bool all_killed(std::vector< std::unique_ptr<Enemy> >);//checks if all unique_ptr are null

private:
    /*
    int rounds; //number of game rounds
    int waves;  //number of waves in a round
    int current_round;
    int current_wave;
    int money;
    */
    int health;
    sf::Clock gameTime;
    const sf::Time delayTime;
    sf::Clock spawnTime;
    sf::Clock moveTime;
    sf::Clock pauseClock;
    float enemyPause = 0;
    float towerPause = 0;
    int enemies = 0;
    std::vector< std::unique_ptr<Enemy> > enemyList;
    std::vector<Tower*> towerList;
    map::Map* map;
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    int speed = 1;

    bool isBuildPhase;
    bool isGamePaused;
};

#endif // GAME_H

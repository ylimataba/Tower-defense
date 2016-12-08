#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "enemy.hpp"
#include "Towers.hpp"
#include "map.hpp"

extern sf::Font getFont();

class Game : public sf::Drawable
{

public:
    Game(map::Map* map);
    ~Game();
    void addTower(sf::Vector2f position, int type);
    void removeTower(std::vector<Tower*>::iterator it);
    bool round_completed();
    void play();
    void set_rounds(std::vector<std::string> rounds);
    //bool health_ok();
    //int getHealth();
    //int getMoney();
    void setIsBuildPhase(bool setPhase);
    bool getIsBuildPhase();
    void setIsGamePaused(bool pauseState);
    bool getIsGamePaused();
    sf::Time getDelayTime();
    void setSpeed(int speedFactor);
    int getSpeed() const;

private:
    std::string current_round;
    //int money;
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
    int speed = 1;
    int points = 0;
    sf::Text score;
    bool isBuildPhase;
    bool isGamePaused;
    std::vector<std::string> rounds;
    void create_enemies(float timeBetweenSpawn);
    void move_enemies();
    void shoot_enemies();
    bool next_round();
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    
    sf::Clock waveDelay;//for delays between waves
    bool first_wave = true;//prevents delay at the start of the round (unless string starts with 't')
    float waveDelayTime = 1.0;//seconds, stackable (ex. "AAAtttttB")
};

#endif // GAME_H

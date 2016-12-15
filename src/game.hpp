#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "enemy.hpp"
#include "Towers.hpp"
#include "map.hpp"
#include <fstream>
#include "save.hpp"

extern sf::Font getFont();

class Game : public sf::Drawable
{

public:
    Game();
    ~Game();
    map::Map* getMap() const;
    void addTower(Tower* tower);
    bool isTower(sf::Vector2f position);
    Tower* getTower(sf::Vector2f position);
    void removeTower(sf::Vector2f position);
    bool round_completed();
    void play();
    void set_rounds(std::vector<std::string> rounds);
    bool health_ok();
    int getHealth();
    int getMoney();
    void addMoney(int amount);
    int getRoundNumber();
    void setIsBuildPhase(bool setPhase);
    bool getIsBuildPhase();
    void setIsGamePaused(bool pauseState);
    bool getIsGamePaused();
    sf::Time getDelayTime();
    void setSpeed(int speedFactor);
    int getSpeed() const;
    void loadRoundsFromFile();
    void sellTower(sf::Vector2f position);
    void upgradeTower(Tower* tower);
    std::vector<std::pair<std::string, std::string>>& getObjectsToSave();
    std::vector<std::pair<std::string, std::string>>& getObjectsToLoad();
    void loadObjects();
    std::string parseObjectMembers(std::pair<std::string, std::string> &object, int memberIndex);
    bool getIsGameOver();
    int getScore();
    void setNewGame();
    bool getNewGame();
    bool getLoadGame();
    void setLoadGame();
    void setCloseWindow();
    bool getCloseWindow();
    void setNextMap(std::string);
    std::string getNextMap();
    void reset();

private:
    bool gameOver;
    bool playerWon;
    int round_number;
    int round_bonus = 100;
    std::string current_round;
    int money;
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
    sf::Text cash;
    sf::Text round;
    sf::Text health_indicator;
    sf::Text game_over;
    sf::Text player_won;
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
    int enemy_id = 0;

    std::vector<std::pair<std::string, std::string>> objectsToSave;
    std::vector<std::pair<std::string, std::string>> objectsToLoad;
    bool loadPreviousGame;
    bool closeWindow;
    bool newGame;
    std::string nextMap;
};

#endif // GAME_H

#include "game.hpp"


Game::Game(map::Map* map)
    : delayTime(sf::milliseconds(1000 / 60)),
      isBuildPhase(true),
      isGamePaused(false),
      map(map)
{
    health = 100;
    //money = 200;
}

Game::~Game(){
    for(auto &enemy : enemyList)
        enemy.reset(nullptr);
    for(auto &tower : towerList)
        delete tower;
}

void Game::create_enemies(float timeBetweenSpawn)
{
    if(!isGamePaused)
        if((enemies == 0 || spawnTime.getElapsedTime().asSeconds() * speed > timeBetweenSpawn + enemyPause) && !current_round.empty()){
            char type = current_round[0];
            switch(type){
                case 'A':
                    enemyList.push_back( std::unique_ptr<Enemy> (new EasyEnemy(map->getEnemyRoute())) );
                    break;
                case 'B':
                    enemyList.push_back( std::unique_ptr<Enemy> (new NormalEnemy(map->getEnemyRoute())) );
                    break;
                case 'C':
                    enemyList.push_back( std::unique_ptr<Enemy> (new HardEnemy(map->getEnemyRoute())) );
                    break;
            }
            current_round.erase(current_round.begin());
            enemies++;
            spawnTime.restart();
            enemyPause = 0;
        }
}

void Game::addTower(sf::Vector2f position, int type)
{
    if(isBuildPhase){
        switch(type)
        {
            case 1:
              {
                Tower* newTower = new BasicTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                break;
              }
            case 2:
              {
                Tower* newTower = new FreezeTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                break;
              }
            case 3:
              {
                Tower* newTower = new PrecisionTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                break;
              }
            case 4:
              {
                Tower* newTower = new BlastTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                break;
              }
        }
    }
}


void Game::removeTower(std::vector<Tower*>::iterator it)
{
    //map->removeTower(/*topLeftCornerOfTower*/);
    this->towerList.erase(it);
}


void Game::move_enemies()
{
    float deltaTime = moveTime.restart().asSeconds();
    if(!isGamePaused){
        for(auto &enemy : enemyList) 
            if(enemy != nullptr){
                enemy->move(deltaTime, speed);
                if(enemy->is_finished()){
                    health--;
                    enemy.reset();
                }
                else if(!enemy->is_alive())
                    enemy.reset();
            }
        enemyList.erase(remove(enemyList.begin(), enemyList.end(), nullptr), enemyList.end());
    }
}

void Game::shoot_enemies()
{
    if(!isGamePaused)
        for(auto tower : this->towerList)
            tower->shoot(enemyList, towerPause, speed);
}

bool Game::round_completed()
{
    if(enemyList.empty() && current_round.empty())
        return true;
    else
        return false;
}

bool Game::next_round()
{
    if(rounds.size() > 1){
        rounds.erase(rounds.begin());
        current_round = rounds[0];
        enemies = 0;
        setIsBuildPhase(true);
        return true;
    }
    return false;
}

void Game::play()
{
    create_enemies(.5f);
    move_enemies(); 
    shoot_enemies();
    if(round_completed())
        next_round();
}

void Game::set_rounds(std::vector<std::string> rounds)
{
    this->rounds = rounds;
    current_round = rounds[0];
}

/*
bool Game::health_ok()
{
    if(this->health > 0)
        return true;
    else
        return false;
}

int Game::getHealth()
{
    return this->health;
}

int Game::getMoney()
{
    return this->money;
}
*/


void Game::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    for(auto &enemy : enemyList)
        if(enemy != nullptr)
            rt.draw(*enemy);
    for(auto tower : towerList)
        rt.draw(*tower);
}

void Game::setIsBuildPhase(bool setPhase)
{
    isBuildPhase = setPhase;
}

bool Game::getIsBuildPhase()
{
    return isBuildPhase;
}

void Game::setIsGamePaused(bool pauseState)
{
    if(!pauseState){
        enemyPause += pauseClock.restart().asSeconds();
        towerPause = enemyPause;
    }
    pauseClock.restart();
    isGamePaused = pauseState;
}

bool Game::getIsGamePaused()
{
    return isGamePaused;
}

sf::Time Game::getDelayTime()
{
    return delayTime;
}

void Game::setSpeed(int speedFactor){
    speed = speedFactor;
}

int Game::getSpeed() const{
    return speed;
}

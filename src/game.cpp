#include "game.hpp"


Game::Game(map::Map* map)
    : delayTime(sf::milliseconds(1000 / 60)),
      isBuildPhase(true),
      isGamePaused(false)
{
    this->map = map;
    health = 100;
    //money = 200;
    //rounds = 5;
    //waves = 4;
    //current_round = 0;
    //current_wave = 0;
}

Game::~Game(){
    for(auto &enemy : enemyList)
        enemy.reset(nullptr);
}

/*
void Game::build()
{
    this->current_round++;
    this->current_wave = 0;
}
*/

bool all_killed(const std::vector< std::unique_ptr<Enemy> > &enemyList)//non-member friend function
{
    if(enemyList.empty()) {
        return true;
    }
    for(auto &enemy : enemyList) {
        if(enemy != nullptr) {
            return false;//return if a single object is found
        }
    }
    return true;//reached if all are nullptr
}

void Game::create_enemies(int numberOfEnemies, float timeBetweenSpawn)
{
    if(!isGamePaused)
        if((enemies == 0 || spawnTime.getElapsedTime().asSeconds() > timeBetweenSpawn + pauseTime) && enemies < numberOfEnemies){
            enemyList.push_back( std::unique_ptr<Enemy> (new Enemy(.5f, 1, 1, map->getEnemyRoute())) );
            enemies++;
            spawnTime.restart();
            pauseTime = 0;
        }
}

void Game::addTower(sf::Vector2f position)
{
    if(isBuildPhase){
        Tower* newTower = new BasicTower(position);
        this->towerList.push_back(newTower);
        map->addTower(position);
    }
}

void Game::removeEnemy(std::vector< std::unique_ptr<Enemy> >::iterator it)
{
    this->enemyList.erase(it);
}


void Game::removeTower(std::vector<Tower*>::iterator it)
{
    //map->removeTower(/*topLeftCornerOfTower*/);
    this->towerList.erase(it);
}


void Game::move_enemies()
{
    float deltaTime = moveTime.restart().asSeconds();
    if(!isGamePaused)
        for(auto &enemy : enemyList) 
            if(enemy != nullptr){
                enemy->move(deltaTime);
                if(enemy->is_finished()){
                    health--;
                    enemy.reset();
                }
                else if(!enemy->is_alive())
                    enemy.reset();
            }
}

void Game::shoot_enemies()
{
    if(!isGamePaused)
        for(auto tower : this->towerList)
            tower->shoot(enemyList);
}

bool Game::round_completed()
{
    //if(enemyList.empty() && enemies > 0)
    if(all_killed(enemyList) && enemies > 0)
    {
        for(auto it = enemyList.begin(); it != enemyList.end(); it++)
        {
            enemyList.erase(it);
        }  
        return true;
    }
    else
        return false;
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

int Game::getRound()
{
    return this->current_round;
}

int Game::getWave()
{
    return this->current_wave;
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
    if(!pauseState)
        pauseTime += pauseClock.restart().asSeconds();
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

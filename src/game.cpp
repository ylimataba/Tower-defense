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
        enemy = nullptr;
        //delete enemy;
}

/*
void Game::build()
{
    this->current_round++;
    this->current_wave = 0;
}
*/
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
    *it = nullptr;
    //this->enemyList.erase(it);
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
        for(auto it = enemyList.begin(); it != enemyList.end(); it++)
        {
            if(*it != nullptr){
                (*it)->move(deltaTime);
                if((*it)->is_finished()){
                    health--;
                    removeEnemy(it);
                    if(enemyList.empty())
                        break;
                }
                else if(!(*it)->is_alive()){
                    removeEnemy(it);
                    if(enemyList.empty())
                        break;
                }
            }
        }
    }
}

void Game::shoot_enemies()
{
    for(auto tower : this->towerList)
    {
        if(!enemyList.empty())
            tower->shoot(enemyList);
        //if enemy gets killed
        //this->money += reward;
        //this->removeEnemy(enemy);
    }
}

bool Game::round_completed()
{
    if(enemyList.empty() && enemies > 0)
        return true;
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

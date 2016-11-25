#include "game.hpp"


Game::Game(map::Map* map)
{
    this->map = map;
    //health = 100;
    //money = 200;
    //rounds = 5;
    //waves = 4;
    //current_round = 0;
    //current_wave = 0;
}

Game::~Game(){
    for(auto enemy : enemyList)
        delete enemy;
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
    if(spawnTime.getElapsedTime().asSeconds() > timeBetweenSpawn)
        if(enemies < numberOfEnemies){
            Enemy* newEnemy = new Enemy(.5f, 1, 1, map->getEnemyRoute());
            enemyList.push_back(newEnemy);
            enemies++;
            spawnTime.restart();
        }
}

/*
void Game::addTower(Tower newTower)
{
    this->towerList.push_back(newTower);
}
*/

void Game::removeEnemy(std::vector<Enemy*>::iterator it)
{
    this->enemyList.erase(it);
}

/*
void Game::removeTower(iterator it)
{
    this->towerList.erase(it);
}
*/

void Game::move_enemies()
{
    float deltaTime = moveTime.restart().asSeconds();
    for(auto it = enemyList.begin(); it != enemyList.end(); it++)
    {
        (*it)->move(deltaTime);
        //if enemy achieves the goal
        //this->health--;
        //this->removeEnemy(enemy);
        if(!((*it)->is_alive()) || (*it)->is_finished()){
            removeEnemy(it);
            if(enemyList.size() == 0)
                break;
        }
    }
}

/*
void Game::shoot_enemies()
{
    for(auto tower : this->towerList)
    {
        tower.shoot();
        //if enemy gets killed
        //this->money += reward;
        //this->removeEnemy(enemy);
    }
}

bool Game::round_completed()
{
    if(!this->enemyList.empty() || this->current_wave < this->waves)
        return false;
    else
        return true;
}

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
    for(auto enemy : enemyList)
        rt.draw(*enemy);
}

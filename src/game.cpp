#include "game.hpp"


Game::Game()
{
    health = 100;
    money = 200;
    rounds = 5;
    waves = 4;
    current_round = 0;
    current_wave = 0;
}

void Game::create_enemies()
{

    int enemies = 5;
    int hitPoints = current_wave;
    int speed = 1;

    for(int i=0; i<enemies; i++)
    {
        Enemy newEnemy = new Enemy(speed, hitPoints, x, y);
        addEnemy(newEnemy);
    }

    this->current_wave++;

}

void Game::addEnemy(Enemy newEnemy)
{
    this->enemyList.push_back(newEnemy);
}

void Game::addTower(Tower newTower)
{
    this->towerList.push_back(newTower);
}

void Game::removeEnemy(iterator it)
{
    this->enemyList.erase(it);
}

void Game::removeTower(iterator it)
{
    this->towerList.erase(it);
}

void Game::move_enemies()
{
    for(auto enemy : this->enemyList)
    {
        enemy.move();
        //if enemy achieves the goal
        //this->health--;
        //this->removeEnemy(enemy);

    }
}

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



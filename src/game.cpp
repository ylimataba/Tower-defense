#include "game.hpp"


Game::Game()
{

}
void Game::create_enemies()
{

    int enemies = 5;
    int hitPoints = current_wave;
    int speed = 1;

    for(int i=0; i<enemies; i++)
    {
        Enemy newEnemy = new Enemy(hitPoints,speed);
        this->enemyList.pushBack(newEnemy);
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

void Game::move_enemies()
{
    for(auto enemy : this->enemyList)
    {
        enemy.move();
    }
}

void Game::shoot_enemies()
{
    for(auto tower : this->towerList)
    {
        tower.shoot();
    }
}

bool Game::round_completed()
{
    if(!this->enemyList.empty() || this->current_wave < this->waves)
        return false;
    else
        return true;
}

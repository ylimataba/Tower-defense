#include <cmath>
#include <vector>
#include "enemy.hpp"


Enemy::Enemy(int s, int h, int val, sf::Vector2f pos, std::vector<sf::Vector2f> r, float slow)
{
    int speed = s;
    int hp= h;
    int value = val;
    sf::Vector2f position = map.getEnemyRoute()[0];
    std::vector<sf::Vector2f> route = map.getEnemyRoute();
    float slow_duration = slow;
}

Enemy::~Enemy(){
}

sf::Vector2f Enemy::get_position()
{
    return this -> position;
}

void Enemy::move()
{

    
    current_position = position;
    sf::Vector2f new_position;
    
    for(int i; i < route.size(); i++)
    {
        if(current_position.x == route[i].x && current_position.y == route[i].y)
        {
            new_position.x = route[i+1].x;
            new_position.y = route[i+1].y;
        }
    }
    
    if ((new_position.x - current_position.x) < 0) // negatiivinen vaakasuunta
    {
        
    }
    
    if ((new_position.x - current_position.x) > 0) // positiivinen vaakasuunta
    {

    }
    
    if ((new_position.y - current_position.y) < 0) // positiivinen pystysuunta
    {

    }
    
    if ((new_position.y - current_position.y) > 0) // negatiivinen pystysuunta
    {

    }
        
    //jos saavuttaa loppupisteen, tekee vahinkoa
}

void Enemy::slow()
{
    this -> slow_duration = 0.5;
}

void Enemy::damage(int amount)
{
    this -> hp -= amount;
}

basehit()
{
    if (this -> position == this -> route[route.size()]
        {
            game.getBaseHp() -= 1;
        }
}
        
void Enemy::draw(map, sprite)
{
    
}




#include <cmath>
#include <vector>
#include "enemy.hpp"



sf::Vector2f Enemy::get_position()
{
    return this -> position;
}

void Enemy::move(float deltaTime, int speedFactor)
{
    float factor = deltaTime + speed;
    slow_duration -= deltaTime;
    if(route.size() > 0)
    {
        sf::Vector2f new_position = route[0];
        sf::Vector2f delta = new_position - position;
        if(this->slow_duration > 0)
        {
            factor = factor/2;
        }
        if(std::abs(delta.x) >= std::abs(delta.y)){
            if( delta.x > 0.f )
            {
                object.move(10.f * factor, 0.f);
            }
            else
            {
                object.move(-10.f * factor, 0.f);
            }
        }
        else if(std::abs(delta.x) < std::abs(delta.y)){
            if( delta.y > 0.f )
            {
                object.move(0.f, 10.f * factor);
            }
            else
            {
                object.move(0.f, -10.f * factor);
            }
        }
        if( std::abs(delta.x) <= 3.f && std::abs(delta.y) <= 3.f ){
            object.setPosition(new_position);
            route.erase(route.begin());
        } 
        position = object.getPosition();
    }
    /*
    else
    {
        Loppupiste saavutettu.
        Tekee vahinkoa
        Katoaa kartalta
    }
    */
}

void Enemy::slow()
{
    this->slow_duration = 30.f;
}

void Enemy::damage(int amount)
{
    this->hp -= amount;
}

bool Enemy::is_alive()
{
    if(this->hp <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


/*
basehit()
{
    if (this -> position == this -> route[route.size()])
        {
            game.getBaseHp() -= 1;
        }
}
*/
        
void Enemy::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
   rt.draw(object);
}

bool Enemy::is_finished()
{
    if(route.size() == 0)
        return true;
    else
        return false;
}

float Enemy::get_travel()//bonus
{
    return travel;
}

float Enemy::get_factor()//bonus
{
    return slow_factor;
}

int Enemy::get_value()//bonus
{
    return value;
}

#include <cmath>
#include <vector>
#include "enemy.hpp"



sf::Vector2f Enemy::get_position()
{
    return this -> object.getPosition();
}

void Enemy::move(float deltaTime, int speedFactor)
{
    float factor = (deltaTime + speed) * 10.f * speedFactor;
    slow_duration -= deltaTime * speedFactor;
    if(route.size() > 0)
    {
        sf::Vector2f new_position = route[0];
        sf::Vector2f delta = new_position - get_position();
        if(this->slow_duration > 0)
        {
            factor = factor/5;
        }
        if(std::abs(delta.x) >= std::abs(delta.y)){
            if( delta.x > 0.f )
            {
                object.move(factor, 0.f);
            }
            else
            {
                object.move(-factor, 0.f);
            }
        }
        else if(std::abs(delta.x) < std::abs(delta.y)){
            if( delta.y > 0.f )
            {
                object.move(0.f, factor);
            }
            else
            {
                object.move(0.f, -factor);
            }
        }
        if( std::abs(delta.x) <= 10.f * speed * speedFactor && std::abs(delta.y) <= 10.f * speed * speedFactor ){
            object.setPosition(new_position);
            route.erase(route.begin());
        } 
        travel += factor;
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
    this->slow_duration = 5.f;
}

int Enemy::damage(int amount)
{
    int points = 0;
    if(this->hp >= amount)
        points = amount;
    else if (hp > 0)
        points = this->hp;
    this->hp -= amount;
    resize();
    return points;
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

float Enemy::get_slow_duration()
{
    return slow_duration;
}


int Enemy::get_index()
{
    return index;
}//for tower memory, to be implemented

void Enemy::set_index(int i)
{
    index = i;
    return;
}//alternative to setting with constructor, delete if not needed when indexing is ready

void Enemy::resize(){
    switch(hp){
        case 1:
            object.setRadius(7.f);
            object.setOrigin(7,7);
            break;
        case 2:
            object.setRadius(10.f);
            object.setOrigin(10,10);
            break;
    }
}

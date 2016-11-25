#include "Towers.hpp"
#include <cmath>
//include shit here ^

//theory finished 22.11.2016
//ruutu = 32x32
//lisää "virhetoleranssi" koordinaatteja  varten


float calc_distance(sf::Vector2f tower, sf::Vector2f target) {
    return sqrt(((tower.x - target.x)*(tower.x - target.x)) 
            + (((tower.y - target.y))*((tower.y - target.y))));
}


bool BasicTower::seekTarget(std::vector<std::unique_ptr<class Enemy>> &enemies)
{
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            d_cmp = calc_distance(position, pos);
            if(d_cmp < dist) {
                target = std::addressof(it);//assign from iterator like this
            }
            else if((d_cmp == dist) && ((*it)->getTravel() > travel)) {
                target = std::addressof(it);
            }
        }
    }
    if(target == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void BasicTower::shoot(&enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget()) {
                (*target)->damage(dmg, 0);
                cooldown = 10;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(clac_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget()) {                                      //new target found
                    (*target)->damage(dmg, 0);
                    cooldown = 10;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg, 0);
                cooldown = 10;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
    }
}

bool FreezeTower::seekTarget(std::vector<std::unique_ptr<class Enemy>> &enemies)
{//prioritize non-frozen
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0;
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position;
            d_cmp = calc_distance(position, pos);
            if(d_cmp < dist) {
                target = std::addressof(it);//assign from iterator like this
            }
            else if((d_cmp == dist) && ((*it)->getTravel() > travel)) {
                target = std::addressof(it);
            }
        }
    }
    if(target == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void FreezeTower::shoot(&enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget()) {
                (*target)->damage(dmg, -1);
                cooldown = 10;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(clac_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget()) {                                      //new target found
                    (*target)->damage(dmg, -1);
                    cooldown = 10;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg, -1);
                cooldown = 10;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
    }
}


bool PrecisionTower::seekTarget(std::vector<std::unique_ptr<class Enemy>> &enemies)
{//aim for highest 'value' stat
    int val = 0;
    sf::Vector2f pos;
    float travel = 0;
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            if(calc_distance(position, pos) <= range) {
                if((*it)->value > val) {
                    target = std::addressof(it);//assign from iterator like this
                }
                else if(((*it)->value == val) && ((*it)->getTravel() > travel)) {
                    target = std::addressof(it);
                }
            }
        }
    }
    if(target == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void PrecisionTower::shoot(&enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget()) {
                (*target)->damage(dmg, 0);
                cooldown = 5;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(clac_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget()) {                                      //new target found
                    (*target)->damage(dmg, 0);
                    cooldown = 5;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg, 0);
                cooldown = 5;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
    }
}


bool BlastTower::seekTarget(std::vector<std::unique_ptr<class Enemy>> &enemies)
{
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; for comparing distance that enemy has traveled,
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            d_cmp = calc_distance(position, pos);
            if(d_cmp < dist) {
                target = std::addressof(it);//assign from iterator like this
            }
            else if((d_cmp == dist) && ((*it)->getTravel() > travel)) {
                target = std::addressof(it);
            }
        }
    }
    if(target == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void BlastTower::shoot(&enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget()) {
                (*target)->damage(dmg, 0);
                (*target)->damage(s_dmg, 1);
                for() {///////////////////////////////////////
                    
                }
                cooldown = 10;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(clac_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget()) {                                      //new target found
                    (*target)->damage(dmg, 0);
                    cooldown = 10;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg, 0);
                cooldown = 10;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
    }
}

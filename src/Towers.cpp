#include "Towers.hpp"
//include shit here ^

//theory finished 22.11.2016

float calc_distance(sf::Vector2f tower, sf::Vector2f target) {
    return sqrt(((tower.x - target.x)*(tower.x - target.x)) 
            + (((tower.y - target.y))*((tower.y - target.y))));
}


bool BasicTower::seekTarget(std::vector<class Enemy*> enemies)
{
    float dist = range;
    float d_cmp;
    //float travel = 0; for comparing distance that enemy has traveled,
    //implementation not ready
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            if( ((*it)->/**/ <= (position.x + range)) 
            && ((*it)->/**/ >= (position.x - range)) 
            && ((*it)->/**/ <= (position.y + range)) 
            && ((*it)->/**/ >= (position.y - range)) ) {//acceptable coordinates
                d_cmp = calc_distance(position, /**/);
                if(d_cmp < dist) {
                    target = std::addressof(it);//assign from iterator like this
                }
                //else if((d_cmp == dist) && (/**/ > travel)) {
                //    target = std::addressof(it);//assignment here once 'travel' is implemented
                //}
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

void BasicTower::shoot()
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
            if(clac_distance(position, /*enemy position*/) > range) {   //out of range
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

bool FreezeTower::seekTarget(std::vector<class Enemy*> enemies)
{//prioritize non-frozen
    float dist = range;
    float d_cmp;
    //float travel = 0;
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            if( ((*it)->/**/ <= (position.x + range)) 
            && ((*it)->/**/ >= (position.x - range)) 
            && ((*it)->/**/ <= (position.y + range)) 
            && ((*it)->/**/ >= (position.y - range)) ) {//acceptable coordinates
                d_cmp = calc_distance(position, /**/);
                if(d_cmp < dist) {
                    target = std::addressof(it);//assign from iterator like this
                }
                //else if((d_cmp == dist) && (/**/ > travel)) {
                //    target = std::addressof(it);//assignment here once 'travel' is implemented
                //}
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

void FreezeTower::shoot()
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
            if(clac_distance(position, /*enemy position*/) > range) {   //out of range
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


bool PrecisionTower::seekTarget(std::vector<class Enemy*> enemies)
{//aim for highest 'value' stat
    int val = 0;
    //float travel = 0;
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            if(calc_distance(position, /**/) <= range) {//acceptable coordinates
                if((*it)->value > val) {
                    target = std::addressof(it);//assign from iterator like this
                }
                //else if(((*it)->value == val) && (/**/ > travel)) {
                //    target = std::addressof(it);//assignment here once 'travel' is implemented
                //}
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

void PrecisionTower::shoot()
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
            if(clac_distance(position, /*enemy position*/) > range) {   //out of range
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


bool BlastTower::seekTarget(std::vector<class Enemy*> enemies)
{
    float dist = range;
    float d_cmp;
    //float travel = 0; for comparing distance that enemy has traveled,
    //implementation not ready
    for(auto it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            if( ((*it)->/**/ <= (position.x + range)) 
            && ((*it)->/**/ >= (position.x - range)) 
            && ((*it)->/**/ <= (position.y + range)) 
            && ((*it)->/**/ >= (position.y - range)) ) {//acceptable coordinates
                d_cmp = calc_distance(position, /**/);
                if(d_cmp < dist) {
                    target = std::addressof(it);//assign from iterator like this
                }
                //else if((d_cmp == dist) && (/**/ > travel)) {
                //    target = std::addressof(it);//assignment here once 'travel' is implemented
                //}
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

void BlastTower::shoot()
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget()) {
                (*target)->damage(dmg, 0);
                (*target)->damage(s_dmg, 1);
                for() {
                    
                }
                cooldown = 10;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(clac_distance(position, /*enemy position*/) > range) {   //out of range
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

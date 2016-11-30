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


/*
bool Tower::isInRange(std::unique_ptr<Enemy> &enemy){
    sf::Vector2f delta = position - enemy->get_position();
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
    return distance <= range;
}
*/

std::unique_ptr<Enemy>* BasicTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            pos = enemy->get_position();
            d_cmp = calc_distance(position, pos);
            if(d_cmp < dist) {
                newtarget = &enemy;//should point to unique_ptr
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                travel = enemy->get_travel();
            }
        }
    }
    return newtarget;
    /*
    consider assignment by index here
    */
}

void BasicTower::shoot(std::vector<std::unique_ptr<Enemy> > &enemies)
{
    if(cooldown < shootTime.getElapsedTime().asSeconds()) {
        if((target == nullptr) or (*target == nullptr)) {
            target = seekTarget(enemies);
        }
        if(target == nullptr) {
            return; 
        }
        else {
            (*target)->damage(dmg);
            shootTime.restart();
            return;
        }
    }
    else {
        return;
    }
}

/*
void BasicTower::shoot(std::vector<std::unique_ptr<Enemy> > &enemies)
{
    if(cooldown < shootTime.getElapsedTime().asSeconds())
        for(auto &enemy : enemies)
            if(enemy != nullptr)
            if( isInRange(enemy)){
                enemy->damage(dmg);
                shootTime.restart();
                break;
            }
}
*/


/*
bool FreezeTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{//prioritize non-frozen
    float dist = range;
    sf::Vector2f pos;
    float s_factor = 0.0;
    float d_cmp;
    float travel = 0;
    for(std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            d_cmp = calc_distance(position, pos);
            if(d_cmp <= range) {
                if((*it)->get_factor() >= s_factor) {
                    if(d_cmp < dist) {
                        target = &(*it);//std::addressof(it);//assign from iterator like this
                        travel = (*target)->get_travel();
                    }
                    else if((d_cmp == dist) && ((*it)->get_travel() > travel)) {
                        target = &(*it);//std::addressof(it);
                        travel = (*target)->get_travel();
                    }
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

void FreezeTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget(enemies)) {
                (*target)->damage(dmg);
                cooldown = 10;
                return;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(calc_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget(enemies)) {                                      //new target found
                    (*target)->damage(dmg);
                    cooldown = 10;
                    return;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg);
                cooldown = 10;
                return;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
        return;
    }
}


bool PrecisionTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{//aim for highest 'value' stat
    int val = 0;
    sf::Vector2f pos;
    float travel = 0;
    for(std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            if(calc_distance(position, pos) <= range) {
                if((*it)->get_value() > val) {
                    target = &(*it);//std::addressof(it);//assign from iterator like this
                    travel = (*target)->get_travel();
                }
                else if(((*it)->get_value() == val) && ((*it)->get_travel() > travel)) {
                    target = &(*it);//std::addressof(it);
                    travel = (*target)->get_travel();
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

void PrecisionTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget(enemies)) {
                (*target)->damage(dmg);
                cooldown = 5;
                return;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(calc_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget(enemies)) {                                      //new target found
                    (*target)->damage(dmg);
                    cooldown = 5;
                    return;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg);
                cooldown = 5;
                return;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
        return;
    }
}


bool BlastTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0;// for comparing distance that enemy has traveled,
    for(std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        if(*it != nullptr) {
            pos = (*it)->get_position();
            d_cmp = calc_distance(position, pos);
            if(d_cmp < dist) {
                target = &(*it);//std::addressof(it);//assign from iterator like this
                travel = (*target)->get_travel();
            }
            else if((d_cmp == dist) && ((*it)->get_travel() > travel)) {
                target = &(*it);//std::addressof(it);
                travel = (*target)->get_travel();
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

void BlastTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if(cooldown <= 0) {                                                 //ready
        if((target == nullptr) || (*target == nullptr)) {               //no target at all
            if(seekTarget(enemies)) {
                (*target)->damage(dmg);
                for(auto it = enemies.begin(); it != enemies.end(); it++) {
                    //splash/explosion damage to nearby enemies
                    if(calc_distance((*target)->get_position(), (*it)->get_position()) <= s_rad) {
                        (*it)->damage(s_dmg);
                    }
                }
                cooldown = 10;
                return;
            }
            else {
                return;
            }
        }
        else {                                                          //has some target
            if(calc_distance(position, (*target)->get_position()) > range) {   //out of range
                if(seekTarget(enemies)) {                                      //new target found
                    (*target)->damage(dmg);
                    for(auto it = enemies.begin(); it != enemies.end(); it++) {
                        //splash/explosion damage to nearby enemies
                        if(calc_distance((*target)->get_position(), (*it)->get_position()) <= s_rad) {
                            (*it)->damage(s_dmg);
                        }
                    }
                    cooldown = 10;
                    return;
                }
                else {                                                  //no targets found
                    target = nullptr;
                    //DO NOT SET "*target" TO NULL!!!
                    return;
                }
            }
            else {                                                      //in range
                (*target)->damage(dmg);
                for(auto it = enemies.begin(); it != enemies.end(); it++) {
                    //splash/explosion damage to nearby enemies
                    if(calc_distance((*target)->get_position(), (*it)->get_position()) <= s_rad) {
                        (*it)->damage(s_dmg);
                    }
                }
                cooldown = 10;
                return;
            }
        }
    }
    else {                                                              //not ready
        cooldown--;
        return;
    }
}
*/

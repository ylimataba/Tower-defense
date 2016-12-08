#include "Towers.hpp"
#include <cmath>
//include shit here ^

//theory finished 22.11.2016
//ruutu = 32x32
//lisää "virhetoleranssi" koordinaatteja  varten


float calc_distance(const sf::Vector2f tower, const sf::Vector2f target) {
    return sqrt(((tower.x - target.x)*(tower.x - target.x)) 
            + (((tower.y - target.y))*((tower.y - target.y))));
}

std::unique_ptr<Enemy>* BasicTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;		// definition 1.12.2016 19:27
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
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
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}

int BasicTower::shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor)
{
    int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime mod 1.12.2016 19:27

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            points = (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}

std::unique_ptr<Enemy>* FreezeTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;		// definition 1.12.2016, continuation
    float dist = range;
    sf::Vector2f pos;
    float s_duration = 30.0;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
            if(d_cmp <= range) {
                if(enemy->get_slow_duration() < s_duration) {
                    newtarget = &enemy;//should point to unique_ptr
                    travel = enemy->get_travel();
                    s_duration = enemy->get_slow_duration();
                }                
                else if(enemy->get_slow_duration() == s_duration) {//might be near-impossible
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
            /*
            if(d_cmp < dist) {
                newtarget = &enemy;//should point to unique_ptr
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                travel = enemy->get_travel();
            }
            */
        }
    }
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}

int FreezeTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
    int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            (*target)->slow();
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}


std::unique_ptr<Enemy>* PrecisionTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;		// definition 1.12.2016, continuation
    float value = 0;
    sf::Vector2f pos;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            if(calc_distance(getCenter(), enemy->get_position()) <= range) {
                if(enemy->get_value() > value) {
                    newtarget = &enemy;//should point to unique_ptr
                    travel = enemy->get_travel();
                }
                else if((enemy->get_value() == value) and (enemy->get_travel() > travel)) {
                    newtarget = &enemy;//should point to unique_ptr
                    travel = enemy->get_travel();
                }
            }
        }
    }
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}

int PrecisionTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
    int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            points = (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}

/*
                SPLASH!!!
                (*target)->damage(dmg);
                for(for(auto &enemy : enemies)) {
                    //splash/explosion damage to nearby enemies
                    if(calc_distance(position, (*target)->get_position()) <= s_rad) {
                        enemy->damage(s_dmg);
                    }
                }
*/

std::unique_ptr<Enemy>* BlastTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;//#newstyle
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
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
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}


int BlastTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
    int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            points = (*target)->damage(dmg);
            for(auto &enemy : enemies) {
                //splash/explosion damage to nearby enemies
                if(calc_distance(enemy->get_position(), (*target)->get_position()) <= s_rad) {
                    points += enemy->damage(s_dmg);
                }
            }
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}

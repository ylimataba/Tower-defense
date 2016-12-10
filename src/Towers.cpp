#include "Towers.hpp"
#include <cmath>
#include <math.h>
//include shit here ^

//theory finished 22.11.2016
//ruutu = 32x32
//lisää "virhetoleranssi" koordinaatteja  varten


float calc_distance(const sf::Vector2f tower, const sf::Vector2f target) {
    return sqrt(((tower.x - target.x)*(tower.x - target.x)) 
            + (((tower.y - target.y))*((tower.y - target.y))));
}

float calc_rotation(const sf::Vector2f tower, const sf::Vector2f target){
    if((tower.y - target.y) >= 0 && (tower.x - target.x) >= 0)    //vasen yla
    {
        float a = acos((tower.x - target.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return a;
    }
    if((tower.y - target.y) <= 0 && (tower.x - target.x) >= 0)    //vasen ala
    {
        float a = acos((tower.x - target.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return -a;
    }
    if((tower.y - target.y) <= 0 && (tower.x - target.x) <= 0)    //oikea ala
    {
        float a = acos((target.x - tower.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return (180 + a);
    }
    if((tower.y - target.y) >= 0 && (tower.x - target.x) <= 0)    //oikea yla
    {
        float a = acos((target.x - tower.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return (180 - a);
    }
    return 0;
}

void Tower::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    if(showRange)
        rt.draw(rangeObject);
    rt.draw(object);
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
            if(enemy->get_index() == e_id) {
                if(calc_distance(getCenter(), enemy->get_position()) <= range) {    
                    newtarget = &enemy;
                    return newtarget;
                }    
            }
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
            if(d_cmp < dist) {
                newtarget = &enemy;//should point to unique_ptr
                dist = d_cmp;
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                dist = d_cmp;
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
    
    if(target != nullptr)
    {
        object.setOrigin(sf::Vector2f(16.0f,16.0f));
        object.setPosition(position + sf::Vector2f(16.0f,16.0f));
        object.setRotation(calc_rotation(getCenter(), (*target)->get_position()));
    }
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
                    dist = d_cmp;
                }                
                else if(enemy->get_slow_duration() == s_duration) {//might be near-impossible
                    if(d_cmp < dist) {
                        newtarget = &enemy;//should point to unique_ptr
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
                    else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                        newtarget = &enemy;//should point to unique_ptr
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
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
                if(enemy->get_index() == e_id) {
                    newtarget = &enemy;
                    return newtarget;
                }
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
    
    if(target != nullptr)
    {
        object.setOrigin(sf::Vector2f(16.0f,16.0f));
        object.setPosition(position + sf::Vector2f(16.0f,16.0f));
        object.setRotation(calc_rotation(getCenter(), (*target)->get_position()));
    }
    
    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            points = (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}


std::unique_ptr<Enemy>* BlastTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;//#newstyle
    float dist = range;
    sf::Vector2f pos;
    float d_cmp;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            if(enemy->get_index() == e_id) {
                if(calc_distance(getCenter(), enemy->get_position()) <= range) {    
                    newtarget = &enemy;
                    return newtarget;
                }    
            }
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
            if(d_cmp < dist) {
                newtarget = &enemy;//should point to unique_ptr
                dist = d_cmp;
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                dist = d_cmp;
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
    if(target != nullptr)
    {
        object.setOrigin(sf::Vector2f(16.0f,16.0f));
        object.setPosition(position + sf::Vector2f(16.0f,16.0f));
        object.setRotation(calc_rotation(getCenter(), (*target)->get_position()));
    }
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

std::unique_ptr<Enemy>* MultiFreezeTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;
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
                    target3 = target2;
                    target2 = newtarget;
                    newtarget = &enemy;//should point to unique_ptr
                    travel = enemy->get_travel();
                    s_duration = enemy->get_slow_duration();
                    dist = d_cmp;
                }                
                else if(enemy->get_slow_duration() == s_duration) {//might be near-impossible
                    if(d_cmp < dist) {
                        target3 = target2;
                        target2 = newtarget;
                        newtarget = &enemy;//should point to unique_ptr
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
                    else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                        target3 = target2;
                        target2 = newtarget;
                        newtarget = &enemy;//should point to unique_ptr
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
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

int MultiFreezeTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
    int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"
    
    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            points = (*target)->damage(dmg);
            (*target)->slow();
            if(target2 != nullptr) {
                points += (*target2)->damage(dmg);
                (*target2)->slow();
                target2 = nullptr;
            }
            if(target3 != nullptr) {
                points += (*target3)->damage(dmg);
                (*target3)->slow();
                target3 = nullptr;
            }
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}

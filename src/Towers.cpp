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
    else if((tower.y - target.y) <= 0 && (tower.x - target.x) >= 0)    //vasen ala
    {
        float a = acos((tower.x - target.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return -a;
    }
    else if((tower.y - target.y) <= 0 && (tower.x - target.x) <= 0)    //oikea ala
    {
        float a = acos((target.x - tower.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return (180 + a);
    }
    else            //if((tower.y - target.y) >= 0 && (tower.x - target.x) <= 0)    oikea yla
    {
        float a = acos((target.x - tower.x)/(calc_distance(tower, target))) * 180.0 / 3.14159f;
        return (180 - a);
    }
}

void Tower::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    if(showRange)
        rt.draw(rangeObject);
    if(hitTime.getElapsedTime().asSeconds() < hit_duration) {//consider separate clock
        rt.draw(hit_object);
    }
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
                //hit_pos = pos;//for hit effects
                dist = d_cmp;
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                //hit_pos = pos;//for hit effects
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
            
            hit_pos.x = ((*target)->get_position().x - 8.f);
            hit_pos.y = ((*target)->get_position().y - 8.f);
            hit_object.setPosition(hit_pos);
            hitTime.restart();
            
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
                    //hit_pos = pos;//for hit effects
                    travel = enemy->get_travel();
                    s_duration = enemy->get_slow_duration();
                    dist = d_cmp;
                }                
                else if(enemy->get_slow_duration() == s_duration) {//might be near-impossible
                    if(d_cmp < dist) {
                        newtarget = &enemy;//should point to unique_ptr
                        //hit_pos = pos;//for hit effects
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
                    else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                        newtarget = &enemy;//should point to unique_ptr
                        //hit_pos = pos;//for hit effects
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
    //int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            (*target)->slow();
            
            hit_pos.x = ((*target)->get_position().x - 8.f);
            hit_pos.y = ((*target)->get_position().y - 8.f);
            hit_object.setPosition(hit_pos);
            hitTime.restart();
            
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return 0;
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
                    //hit_pos = pos;//for hit effects
                    return newtarget;
                }
                if(enemy->get_value() > value) {
                    newtarget = &enemy;//should point to unique_ptr
                    //hit_pos = pos;//for hit effects
                    travel = enemy->get_travel();
                }
                else if((enemy->get_value() == value) and (enemy->get_travel() > travel)) {
                    newtarget = &enemy;//should point to unique_ptr
                    //hit_pos = pos;//for hit effects
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
            
            hit_pos.x = ((*target)->get_position().x - 16.f);
            hit_pos.y = ((*target)->get_position().y - 16.f);
            hit_object.setPosition(hit_pos);
            hitTime.restart();
            
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
                    //hit_pos = pos;//for hit effects
                    return newtarget;
                }    
            }
            pos = enemy->get_position();
            d_cmp = calc_distance(getCenter(), pos);
            if(d_cmp < dist) {
                newtarget = &enemy;//should point to unique_ptr
                //hit_pos = pos;//for hit effects
                dist = d_cmp;
                travel = enemy->get_travel();
            }
            else if((d_cmp == dist) && (enemy->get_travel() > travel)) {
                newtarget = &enemy;//should point to unique_ptr
                //hit_pos = pos;//for hit effects
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
            
            hit_object.setScale(sf::Vector2f(3.4375, 3.4375));
            hit_pos.x = ((*target)->get_position().x - s_rad);
            hit_pos.y = ((*target)->get_position().y - s_rad);
            hit_object.setPosition(hit_pos);
            hitTime.restart();
            
            shootTime.restart();
            pauseTime = 0;
        }
    }
    return points;
}

void MultiFreezeTower::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    if(showRange)
        rt.draw(rangeObject);
    if(hitTime.getElapsedTime().asSeconds() < hit_duration) {//consider separate clock
        rt.draw(hit_object);
        rt.draw(hit_object2);
        rt.draw(hit_object3);
    }
    rt.draw(object);
}

std::unique_ptr<Enemy>* MultiFreezeTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;
    target2 = nullptr;
    target3 = nullptr;
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
                //fill if there are nullptr..?
                if(enemy->get_slow_duration() < s_duration) {
                    target3 = target2;
                    target2 = newtarget;
                    newtarget = &enemy;//should point to unique_ptr
                    travel = enemy->get_travel();
                    s_duration = enemy->get_slow_duration();
                    dist = d_cmp;
                }                
                else if(enemy->get_slow_duration() == s_duration) {//might be near-impossible
                    if(enemy->get_travel() >= travel) {
                        target3 = target2;
                        target2 = newtarget;
                        newtarget = &enemy;//should point to unique_ptr
                        travel = enemy->get_travel();
                        s_duration = enemy->get_slow_duration();
                        dist = d_cmp;
                    }
                }
                else {//messy, toxic and sensitive crap below, DO NOT TOUCH! (for now)
                    if((*newtarget != enemy)) {
                        //if null or better
                        if(target2 != nullptr) {
                            if(enemy->get_slow_duration() < (*target2)->get_slow_duration()) {
                                target2 = &enemy;
                            }
                        }
                        else {
                            target2 = &enemy;
                        }
                    }
                    if((*newtarget != enemy) and (*target2 != enemy)) {
                        if((target3 != nullptr)) {
                            if(enemy->get_slow_duration() < (*target3)->get_slow_duration()) {
                                target3 = &enemy;
                            }
                        }
                        else {
                            target3 = &enemy;
                        }
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
    //int points = 0;
    std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"
    
    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target != nullptr) {
            (*target)->slow();
            
            hit_pos.x = ((*target)->get_position().x - 8.f);
            hit_pos.y = ((*target)->get_position().y - 8.f);
            hit_object.setPosition(hit_pos);
            
            target = nullptr;
        }
        else {
            hit_object.setPosition(-40.0,0.0);//offscreen
        }
        if(target2 != nullptr) {
            (*target2)->slow();
            
            hit_pos2.x = ((*target2)->get_position().x - 8.f);
            hit_pos2.y = ((*target2)->get_position().y - 8.f);
            hit_object2.setPosition(hit_pos2);
            
            target2 = nullptr;
        }
        else {
            hit_object2.setPosition(-40.0,0.0);
        }
        if(target3 != nullptr) {
            (*target3)->slow();
            
            hit_pos3.x = ((*target3)->get_position().x - 8.f);
            hit_pos3.y = ((*target3)->get_position().y - 8.f);
            hit_object3.setPosition(hit_pos3);
            
            target3 = nullptr;
        }
        else {
            hit_object3.setPosition(-40.0,0.0);
        }
        
        hitTime.restart();
        shootTime.restart();
        pauseTime = 0;
    }
    return 0;
}

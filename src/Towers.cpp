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


/*
bool Tower::isInRange(std::unique_ptr<Enemy> &enemy){
    sf::Vector2f delta = position - enemy->get_position();
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
    return distance <= range;
}
*/

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
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}

void BasicTower::shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor)
{
	std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime mod 1.12.2016 19:27

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(*target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(calc_distance(position, (*target)->get_position()) > range) {
            target = seekTarget(enemies);
        }
        
        if(target == nullptr) {
            return; 
        }
        else if(*target == nullptr) {
            return;
        }
        else {
            (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
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
            d_cmp = calc_distance(position, pos);
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
/*
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
*/

void FreezeTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
	std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(*target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(calc_distance(position, (*target)->get_position()) > range) {
            target = seekTarget(enemies);
        }
        
        if(target == nullptr) {
            return; 
        }
        else if(*target == nullptr) {
            return;
        }
        else {
            (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
            return;
        }
    }
    else {
        return;
    }
}


std::unique_ptr<Enemy>* PrecisionTower::seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::unique_ptr<Enemy> *newtarget = nullptr;		// definition 1.12.2016, continuation
    float value = 0;
    sf::Vector2f pos;
    float travel = 0; //for comparing distance that enemy has traveled,
    for(auto &enemy : enemies) {
        if(enemy != nullptr) {
            if(calc_distance(position, enemy->get_position()) <= range) {
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

void PrecisionTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
	std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(*target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(calc_distance(position, (*target)->get_position()) > range) {
            target = seekTarget(enemies);
        }
        
        if(target == nullptr) {
            return; 
        }
        else if(*target == nullptr) {
            return;
        }
        else {
            (*target)->damage(dmg);
            shootTime.restart();
            pauseTime = 0;
            return;
        }
    }
    else {
        return;
    }
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
    if(newtarget != nullptr) {//maybe unnecessary if-else
        return newtarget;
    }
    else {
        return nullptr;
    }
}


void BlastTower::shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor)
{
	std::unique_ptr<Enemy> *target = seekTarget(enemies);	// seek target everytime continuity from "mod 1.12.2016 19:27"

    if(cooldown + pauseTime < shootTime.getElapsedTime().asSeconds() * speedFactor) {
        if(target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(*target == nullptr) {
            target = seekTarget(enemies);
        }
        else if(calc_distance(position, (*target)->get_position()) > range) {
            target = seekTarget(enemies);
        }
        
        if(target == nullptr) {
            return; 
        }
        else if(*target == nullptr) {
            return;
        }
        else {
            (*target)->damage(dmg);
            for(auto &enemy : enemies) {
                //splash/explosion damage to nearby enemies
                if(calc_distance(position, (*target)->get_position()) <= s_rad) {
                    enemy->damage(s_dmg);
                }
            }
            shootTime.restart();
            pauseTime = 0;
            return;
        }
    }
    else {
        return;
    }
}

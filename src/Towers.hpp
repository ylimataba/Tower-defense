#ifndef Towers_hpp
#define Towers_hpp

#include <memory>

/*          theory finished 22.11.2016
TYPES:
    -Basic: SKETCHED, NOT YET TESTED
    -Precision (target most "valuable" enemies, fast shots): SKETCHED, NOT YET TESTED
    -Freeze (movement speed reduction): SKETCHED, NOT YET TESTED
    -Blast (damage target and all nearby enemies): WIP
    -Volley (multiple targets): WIP
*/
//consider remaking init. list; might require changes to "builder" part of the program

/*
typedef struct bounds {
    float x1;
    float x2;
    float y1;
    float y2;
}optimointia varten, sovitetaan luokkaan myöhemmin
*/

float calc_distance(sf::Vector2f tower, sf::Vector2f target);

class Tower {
public:
    Tower(int h, float r, int d, sf::Vector2f pos)
    {
        hp = h;
        range = r;
        dmg = d;
        position.x = pos.x;
        position.y = pos.y;
    }
    //sf::Vector2f getPos() {return position}
    //int getHp() {return hp}
    //float getRange() {return range}
    //void draw();
    virtual bool seekTarget() = 0;
    virtual void shoot() = 0;
private:
    sf::Vector2f position;
    int hp;
    float range;
    int dmg;
    int cooldown = 0;
    std::unique_ptr<class Enemy> *target = nullptr;//use .get()??
}

class BasicTower : public Tower {
public:
    BasicTower(sf::Vector2f pos) : Tower(100, 50, 1, pos) { }
    bool seekTarget();
    void shoot();
}


class FreezeTower : public Tower
{
public:
    FreezeTower(sf::Vector2f pos) : Tower(100, 50, 1, pos) { }
    bool seekTarget();
    void shoot();
}

class PrecisionTower : public Tower
{
public:
    PrecisionTower(sf::Vector2f pos) : Tower(100, 120, 2, pos) { }
    bool seekTarget();
    void shoot();
}
/*
class BlastTower : public Tower
{
public:
    BlastTower(int h, float r, int d, sf::Vector2f pos, 
            const  std::vector<sf::Vector2f>& map) : 
        Tower(h, r, d, pos, 
            const std::vector<sf::Vector2f>& path) { s_dmg = d/2; s_rad = ?? }
    bool seekTarget(std::vector<class Enemy*> enemies);
    void shoot();
private:
    int s_dmg;
    float s_rad;
}

class VolleyTower
{
    //needs private members target2 and target 3
    //track least needed pointer ie. null or farthest etc.
}
*/

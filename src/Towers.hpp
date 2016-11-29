#ifndef Towers_hpp
#define Towers_hpp

#include <memory>
#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "enemy.hpp"


/*
TYPES:
    -Basic: SKETCHED, NOT YET TESTED
    -Precision (target most "valuable" enemies, fast shots): SKETCHED, NOT YET TESTED
    -Freeze (movement speed reduction): SKETCHED, NOT YET TESTED
    -Blast (damage target and all nearby enemies): SKETCHED, NOT YET TESTED
    -Volley (multiple targets): WIP
*/


/*
typedef struct bounds {
    float x1;
    float x2;
    float y1;
    float y2;
}ei varmaan tarvita
*/

float calc_distance(sf::Vector2f tower, sf::Vector2f target);

class Tower : public sf::Drawable {
public:
    Tower(int h, float r, int d, sf::Vector2f pos) :
        hp(h),
        range(r),
        dmg(d),
        position(pos)
    { };
    virtual ~Tower() { };
    //sf::Vector2f getPos() {return position};
    //int getHp() {return hp};
    //float getRange() {return range};
    //virtual Enemy* seekTarget(std::vector<Enemy*> &enemies) = 0;
    virtual void shoot(std::vector<std::unique_ptr<Enemy> > &enemies) = 0;
    bool isInRange(std::unique_ptr<Enemy>&);
protected:
    sf::Vector2f position;
    int hp;
    float range;
    int dmg;
    float cooldown = 0;
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const = 0;
    sf::RectangleShape object;
    sf::Clock shootTime;
};

class BasicTower : public Tower {
public:
    BasicTower(sf::Vector2f pos) : Tower(100, 50.0, 1, pos) {
        object.setSize(sf::Vector2f(32.f, 32.f));
        object.setPosition(pos);
        object.setFillColor(sf::Color::Black);
        cooldown = 3.f;
    };
    //Enemy* seekTarget(std::vector<Enemy*> &enemies);
    void shoot(std::vector<std::unique_ptr<Enemy> > &enemies);
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};

/*
class FreezeTower : public Tower
{
public:
    FreezeTower(sf::Vector2f pos) : Tower(100, 50.0, 1, pos) { }
    virtual bool seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    virtual void shoot(std::vector<std::unique_ptr<Enemy>> &enemies);
};

class PrecisionTower : public Tower
{
public:
    PrecisionTower(sf::Vector2f pos) : Tower(100, 120.0, 2, pos) { }
    virtual bool seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    virtual void shoot(std::vector<std::unique_ptr<Enemy>> &enemies);
};

class BlastTower : public Tower
{
public:
    BlastTower(sf::Vector2f pos) : Tower(100, 50.0, 2, pos) { s_dmg = 1; s_rad = 8.0; }
    virtual bool seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    virtual void shoot(std::vector<std::unique_ptr<Enemy>> &enemies);
private:
    int s_dmg;
    float s_rad;
};

class VolleyTower
{
    //needs private members target2 and target 3
    //track least needed pointer ie. null or farthest etc.
}
*/

float calc_distance(sf::Vector2f tower, sf::Vector2f target);
#endif

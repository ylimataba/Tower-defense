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
    {
        rangeObject.setRadius(range);
        rangeObject.setOrigin(range, range);
        rangeObject.setPosition(getCenter());
        rangeObject.setFillColor(sf::Color(255, 255, 255, 50));
    };
    virtual ~Tower() { };
    sf::Vector2f getPos() const {return position;};
    //int getHp() {return hp};
    //float getRange() {return range};
    void toggleRange(){if(showRange) showRange = false; else showRange = true;};
    virtual std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies) = 0;
    virtual int shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor) = 0;
protected:
    sf::Vector2f position;
    int hp;
    float range;
    int dmg;
    float cooldown = 0;
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    sf::RectangleShape object;
    sf::Clock shootTime;
    sf::Vector2f getCenter() const{
        return position + sf::Vector2f(16.f, 16.f);
    };
    bool showRange = false;
    sf::CircleShape rangeObject;
    //std::unique_ptr<Enemy> *target = nullptr;		removed 1.12.2016 19:27
    //int e_id = 0; for later
};

class BasicTower : public Tower {
public:
    BasicTower(sf::Vector2f pos) : Tower(100, 50.0, 1, pos) {
        object.setSize(sf::Vector2f(32.f, 32.f));
        object.setPosition(pos);
        object.setFillColor(sf::Color::Black);
        cooldown = 3.f;
    };
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor);
};


class FreezeTower : public Tower
{
public:
    FreezeTower(sf::Vector2f pos) : Tower(100, 50.0, 1, pos) {
        object.setSize(sf::Vector2f(32.f, 32.f));
        object.setPosition(pos);
        object.setFillColor(sf::Color::Blue);
        cooldown = 1.f;
    };
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
};

class PrecisionTower : public Tower
{
public:
    PrecisionTower(sf::Vector2f pos) : Tower(100, 120.0, 2, pos) {
        object.setSize(sf::Vector2f(32.f, 32.f));
        object.setPosition(pos);
        object.setFillColor(sf::Color::White);
        cooldown = 1.5;
    }
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
};

class BlastTower : public Tower
{
public:
    BlastTower(sf::Vector2f pos) : Tower(100, 70.0, 2, pos) {
        object.setSize(sf::Vector2f(32.f, 32.f));
        object.setPosition(pos);
        object.setFillColor(sf::Color::Red);
        cooldown = 3.f;
        
        s_dmg = 1;
        s_rad = 25.0;
    }
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
private:
    int s_dmg;
    float s_rad;
};

/*
class VolleyTower, might just scrap this
{
    //needs private members target2 and target 3
    //track least needed pointer ie. null or farthest etc.
}
*/

float calc_distance(sf::Vector2f tower, sf::Vector2f target);
#endif

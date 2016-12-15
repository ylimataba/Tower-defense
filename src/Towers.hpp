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
float calc_rotation(sf::Vector2f tower, sf::Vector2f target);

class Tower : public sf::Drawable {
public:
    Tower(int h, float r, int d) :
        hp(h),
        range(r),
        dmg(d)
    {
        position = sf::Vector2f(0,0);
        rangeObject.setRadius(range);
        rangeObject.setOrigin(range, range);
        rangeObject.setPosition(getCenter());
        rangeObject.setFillColor(sf::Color(255, 255, 255, 50));
    };
    virtual ~Tower() { };
    sf::Vector2f getPos() const {return position;};
    //int getHp() {return hp};
    //float getRange() {return range};
    void setPosition(sf::Vector2f pos){ position = pos; object.setPosition(pos); rangeObject.setPosition(getCenter());};
    void toggleRange(){if(showRange) showRange = false; else showRange = true;};
    virtual std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies) = 0;
    virtual int shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor) = 0;
    int get_cost() {return cost;}
    int get_type() {return type;}

protected:
    int type;
    sf::Vector2f position;
    int hp;
    float range;
    int dmg;
    float cooldown = 0;
    int cost;
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    
    sf::Sprite object;
    sf::Texture texture;
    
    sf::Sprite hit_object;
    sf::Texture hit_texture;
    sf::Vector2f hit_pos;
    sf::Clock hitTime;
    float hit_duration = 0.1;
    
    sf::Clock shootTime;
    sf::Vector2f getCenter() const{
        return position + sf::Vector2f(16.f, 16.f);
    };
    bool showRange = true;
    sf::CircleShape rangeObject;
    //std::unique_ptr<Enemy> *target = nullptr;		removed 1.12.2016 19:27
    int e_id = -1;
};

class BasicTower : public Tower {
public:
    BasicTower() : Tower(100, 50.0, 1) {
        texture.loadFromFile("../maps/Basic.png");
        object.setTexture(texture);
        object.setPosition(position);
        
        hit_texture.loadFromFile("../maps/TD_hit_yellow.png");
        hit_object.setTexture(hit_texture);
        hit_object.setPosition(0.0,0.0);
        
        cooldown = 1.0f;
        cost = 200;
        type = 11;
    };
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy> > &enemies, float& pauseTime, int speedFactor);
};


class FreezeTower : public Tower
{
public:
    FreezeTower() : Tower(100, 50.0, 1) {
        texture.loadFromFile("../maps/Freeze.png");
        object.setTexture(texture);
        object.setPosition(position);
        
        hit_texture.loadFromFile("../maps/TD_hit_icy.png");
        hit_object.setTexture(hit_texture);
        hit_object.setPosition(-40.0,0.0);
        
        cooldown = 1.0f;
        cost = 300;
        type = 12;
    };
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
};

class PrecisionTower : public Tower
{
public:
    PrecisionTower() : Tower(100, 120.0, 2) {
        texture.loadFromFile("../maps/TD_precision_alternative_32.png");
        object.setTexture(texture);
        object.setPosition(position);
        
        hit_texture.loadFromFile("../maps/TD_precision_hit_32.png");
        hit_object.setTexture(hit_texture);
        hit_object.setPosition(-40.0,0.0);
        
        cooldown = 0.4f;
        cost = 1000;
        type = 23;
    }
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
};

class BlastTower : public Tower
{
public:
    BlastTower() : Tower(100, 70.0, 2) {
        texture.loadFromFile("../maps/Blast.png");
        object.setTexture(texture);
        object.setPosition(position);
        
        hit_texture.loadFromFile("../maps/TD_blast_hit_32.png");
        hit_object.setTexture(hit_texture);
        hit_object.setPosition(-40.0,0.0);
        
        cooldown = 1.0f;
        cost = 700;
        type = 21;
        
        s_dmg = 2;
        s_rad = 55.0;
        //eff_scale = 3.4375;
    }
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
private:
    float eff_scale;
    int s_dmg;
    float s_rad;
};

class MultiFreezeTower : public Tower
{
public:
    MultiFreezeTower() : Tower(100, 90.0, 0) {
        texture.loadFromFile("../maps/Freeze.png");
        object.setTexture(texture);
        object.setPosition(position);
        
        hit_texture.loadFromFile("../maps/TD_hit_icy.png");
        
        hit_object.setTexture(hit_texture);
        hit_object.setPosition(-40.0,0.0);
        
        hit_object2.setTexture(hit_texture);
        hit_object2.setPosition(-40.0,0.0);
        
        hit_object3.setTexture(hit_texture);
        hit_object3.setPosition(-40.0,0.0);
        
        cooldown = 1.f;
        cost = 200;
        type = 22;
    };
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    std::unique_ptr<Enemy>* seekTarget(std::vector<std::unique_ptr<Enemy>> &enemies);
    int shoot(std::vector<std::unique_ptr<Enemy>> &enemies, float& pauseTime, int speedFactor);
private:
    std::unique_ptr<Enemy> *target2 = nullptr;
    std::unique_ptr<Enemy> *target3 = nullptr;
    
    sf::Sprite hit_object2;
    sf::Vector2f hit_pos2;
    sf::Sprite hit_object3;
    sf::Vector2f hit_pos3;
};
/*
class VolleyTower, might just scrap this
{
    //needs private members target2 and target 3
    //track least needed pointer ie. null or farthest etc.
}
*/

//float calc_distance(sf::Vector2f tower, sf::Vector2f target);
#endif

#ifndef Enemy_hpp
#define Enemy_hpp

#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"


class Enemy : public sf::Drawable 
{
    public:
        Enemy(float s, int h, int v, std::vector<sf::Vector2f> r) :
            speed(s),
            hp(h),
            value(v),
            route(r)
            { };
        virtual ~Enemy() { };
        virtual sf::Vector2f get_position();
        virtual void move(float deltaTime, int speedFactor); // deltaTime = GameClock.restart().asSeconds();
        virtual void slow();
        int damage(int amount);

        bool is_alive();
        bool is_finished();

        float get_travel();
        float get_factor();
        float get_slow_duration();
        int get_value();
        //void basehit();
    
    
    protected:
        float speed;        // .1f is good value for example
        int hp;
        int value;
        std::vector<sf::Vector2f> route;
        float slow_factor = 1;
        float slow_duration = 0.f;
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const = 0;
        float travel = 0;

        // object could be sprite but at this point circle will do fine
        sf::CircleShape object; 
};


class EasyEnemy : public Enemy {
public:
    EasyEnemy(std::vector<sf::Vector2f> route) : Enemy(0.3f, 1, 1, route) {
        // set up circle
        object.setRadius(7.f);
        object.setOutlineThickness(3);
        object.setOutlineColor(sf::Color::Black);
        object.setFillColor(sf::Color::Red);
        object.setOrigin(7.f, 7.f);
        object.setPosition(route[0]);
    };

    
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};

class NormalEnemy : public Enemy {
public:
    NormalEnemy(std::vector<sf::Vector2f> route) : Enemy(0.5f, 2, 1, route) {
        // set up circle
        object.setRadius(10.f);
        object.setOutlineThickness(3);
        object.setOutlineColor(sf::Color::Black);
        object.setFillColor(sf::Color::Blue);
        object.setOrigin(10.f, 10.f);
        object.setPosition(route[0]);
    };
    
    
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};

class HardEnemy : public Enemy {
public:
    HardEnemy(std::vector<sf::Vector2f> route) : Enemy(0.6f, 3, 1, route) {
        // set up circle
        object.setRadius(12.f);
        object.setOutlineThickness(3);
        object.setOutlineColor(sf::Color::Black);
        object.setFillColor(sf::Color::Black);
        object.setOrigin(12.f, 12.f);
        object.setPosition(route[0]);
    };
    
    
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};
#endif

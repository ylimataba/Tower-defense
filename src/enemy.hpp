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
        void damage(int amount);

        bool is_alive();
        bool is_finished();

        float get_travel();
        float get_factor();
        int get_value();
        //void basehit();
    
    
    protected:
        float speed;        // .1f is good value for example
        int hp;
        int value;
        sf::Vector2f position;
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
    EasyEnemy(std::vector<sf::Vector2f> route) : Enemy(0.5f, 1, 1, route) {
        // set up circle
        object.setPosition(route[0]);
        object.setRadius(10.f - 3);
        object.setOutlineThickness(3);
        object.setOutlineColor(sf::Color::Black);
        object.setFillColor(sf::Color::White);
        object.setOrigin(10.f / 2, 10.f / 2);
    };

    
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};

class NormalEnemy : public Enemy {
public:
    NormalEnemy(std::vector<sf::Vector2f> route) : Enemy(0.5f, 1, 1, route) {
        // set up circle
        object.setPosition(route[0]);
        object.setRadius(10.f);
        object.setOutlineThickness(3);
        object.setOutlineColor(sf::Color::Black);
        object.setFillColor(sf::Color::Black);
        object.setOrigin(10.f / 2, 10.f / 2);
    };
    
    
private:
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const{
        rt.draw(object);
    };
};

class hardEnemy : public Enemy
{
    
};
#endif

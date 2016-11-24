#ifndef Enemy_hpp
#define Enemy_hpp

#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"


class Enemy : public sf::Drawable 
{
    public:
        Enemy(float s, int h, int v, std::vector<sf::Vector2f> r);
        ~Enemy();
        void move(float deltaTime); // deltaTime = GameClock.restart().asSeconds();
        sf::Vector2f get_position();
        void damage(int amount);
        void slow();
        void basehit();
    
    private:
        float speed; // .1f is good value for example
        int hp;
        int value;
        sf::Vector2f position;
        std::vector<sf::Vector2f> route;
        float slow_duration = 0;
        void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

        // object could be sprite but at this point circle will do fine
        sf::CircleShape object; 
};


class easyEnemy : public Enemy
{

};
class normalEnemy : public Enemy
{

};
class hardEnemy : public Enemy
{
    
};
#endif

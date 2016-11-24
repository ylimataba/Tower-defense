#ifndef Enemy_hpp
#define Enemy_hpp

#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"


class Enemy
{
    public:
        Enemy(int s, int h, int v, sf::Vector2f pos, std::vector<sf::Vector2f> r);
        ~Enemy();
        void move();
        sf::Vector2f get_position();
        void draw();
        void damage(int amount);
        void slow();
        void basehit();
    
    private:
        int speed;
        int hp;
        int value;
        sf::Vector2f position;
        std::vector<sf::Vector2f> route;
        slow_duration = 0;
        //sprite
};


class easyEnemy : public Enemy
{

}
class normalEnemy : public Enemy
{

}
class hardEnemy : public Enemy
{
    
}
#endif

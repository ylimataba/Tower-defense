//
//  Enemy.hpp
//  TowerDefence
//
//  Created by Pyry Viita-aho on 18.11.2016.
//  Copyright © 2016 Pyry Viita-aho. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <Vector2.hpp>


Class Enemy
{
public:
    Enemy(int speed, int hp, int value, float x, float y);
    void move();
    sf::Vector2f get_position();
    draw();
    damage();
    slow();
    basehit();
    
private:
    int speed;
    int hp;
    int value;
    sf::Vector2f position;
    v1.x = 18.2f;
    float y = v1.y;
    float x = v1.x;
    std::vector<sf::Vector2f> path;
    
    //sprite
}



#endif /* Enemy_hpp */

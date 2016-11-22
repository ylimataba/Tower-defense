#ifndef TOWERDEFENCE_MAP_HH
#define TOWERDEFENCE_MAP_HH

#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>

static const std::string PATH_TO_MAPS = "../maps/";

namespace map {

class Map : public sf::Drawable {
    public:
        Map(const std::string& filename);
        ~Map();
        std::vector<sf::Vector2f> getEnemyRoute();
        //bool checkCollision(sf::Vector2f coordinates);
    private: 
        tmx::MapLoader* map;
        std::vector<sf::Vector2f> enemyRoute;
        std::vector<sf::Vector2f> points;
        sf::Vector2f position;
        void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

};
} // namespace map


#endif

#include "map.hpp"

namespace map {

Map::Map(const std::string& filename) {
    map = new tmx::MapLoader(PATH_TO_MAPS);
    map->Load(filename);

    for(auto layer : map->GetLayers())
        if(layer.name == "Enemies")
            for(auto object : layer.objects)
                if(object.GetName() == "Route"){
                    std::vector<sf::Vector2f> points = object.PolyPoints();
                    sf::Vector2f position = object.GetPosition();
                    for(auto point : points)
                        enemyRoute.push_back(point + position);
                    break;
                }
}

Map::~Map(){
    delete map;
}

std::vector<sf::Vector2f> Map::getEnemyRoute() const{
    return enemyRoute;
}

void Map::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    rt.draw(*map);
}

bool Map::isCollision(std::vector<sf::Vector2f> collisionPoints){
    for(auto layer : map->GetLayers()){
        if(layer.name == "Collision")
            for(auto object : layer.objects)
                for(auto point : collisionPoints)
                    if(object.Contains(point))
                        return true;
    }
    return false;
}
    
} // namespace map

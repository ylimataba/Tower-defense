#include "map.hpp"

namespace map {

Map::Map(const std::string& filename) {
    map = new tmx::MapLoader(PATH_TO_MAPS);
    map->Load(filename);
    for(auto layer : map->GetLayers()){
        if(layer.name == "Enemies"){
            for(auto object : layer.objects){
                if(object.GetName() == "Route"){
                    points = object.PolyPoints();
                    position = object.GetPosition();
                    break;
                }
            }
        }
    }
    for(auto point : points){
        enemyRoute.push_back(point + position);
    }
}

Map::~Map(){
    delete map;
}

std::vector<sf::Vector2f> Map::getEnemyRoute(){
    return enemyRoute;
}

void Map::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    rt.draw(*map);
}

} // namespace map

#include "menuObjects.hpp"

class HighScore : public sf::Drawable {
    public:
        HighScore(){};
        HighScore(sf::Font* font, Game* game);
        ~HighScore(){};
        void getUsername(sf::Event event);
        void addScore();
        void showScores();
        void hideScores();
        bool isShowing();
        void readScores();
        void writeScores();
        std::vector<sf::Text> getScores() const;
        std::vector<std::pair<gui::Menu,gui::Text> > getBoxes() const;
        void setAddingTrue();
    
    private:
        sf::Font* font;
        Game* game;
        std::string filepath;
        std::vector<std::pair<std::string, int> > scores;
        bool adding = true;
        bool show = false;
        std::string username = "";
        sf::Vector2f first_position = sf::Vector2f((MAP_WIDTH-224)/2, (MAP_HEIGHT-480)/2);
        sf::Vector2f delta_score2score = sf::Vector2f(0,48);
        sf::Vector2f box_size = sf::Vector2f(MAP_TILE_SIZE,MAP_TILE_SIZE);
        sf::Vector2f box_position = sf::Vector2f((MAP_WIDTH-128)/2, (MAP_HEIGHT/3)*2);
        sf::Vector2f delta_box = sf::Vector2f(48,0);
        sf::Text addText;
        void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
};

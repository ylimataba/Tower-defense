#ifndef TOWER_DEFENCE_SRC_WINDOW_HPP
#define	TOWER_DEFENCE_SRC_WINDOW_HPP

#include "menuObjects.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Towers.hpp"
#include <SFML/Window.hpp>
#include <cstddef>
#include "highscore.hpp"

class Window : public sf::RenderWindow
{
public:
	Window(std::string title, map::Map *map, Game *game);

	~Window();

	sf::Vector2f getMousePosition();
	sf::Vector2f getCurrentMapTile();

	void drawAll();

	void updateTowerPlacer();
	void setTowerPlacerRange(float newRange);
	float getTowerPlacerRange();

	bool isCollision();
	bool isInGameArea();

	void checkEvents();

private:
	Window(const Window&);
	Window& operator=(const Window&);

	void createMenus();
	void createButtons();
	void createTexts();
	void createBars();

	void buttonPress();
	void buttonRelease();
	
	map::Map *m_map;
	Game *m_game;

	gui::Menu m_sideMenu;
	gui::Menu m_bottomMenu;
	gui::Menu m_mapMenu;

	gui::NormalButton m_saveButton;
	gui::NormalButton m_playButton;
	gui::NormalButton m_speedButton;
	gui::NormalButton m_mapButton;
	gui::NormalButton m_loadButton;
        gui::NormalButton m_scoresButton;

	gui::Text m_saveButtonText;
	gui::Text m_playButtonText;
	gui::Text m_speedButtonText;
	gui::Text m_mapButtonText;
	gui::Text m_loadButtonText;
        gui::Text m_scoresButtonText;

	gui::TowerButton m_tower1Button;
	gui::TowerButton m_tower2Button;
	gui::TowerButton m_tower3Button;
    gui::TowerButton m_tower4Button;

	gui::Bar m_lifeBar;
	gui::Bar m_textBar;
	gui::Text m_textBarText;

	sf::Vector2f m_mousePosition;

	bool m_isMapBeingSelected;
	int m_currentMapNumber;
	int m_selectedMapNumber;

	bool m_isTowerBeingBuilt;
	gui::Towers m_towerBeingBuilt;
	gui::TowerMenu m_towerMenu;
	Tower *m_tower = nullptr;

        HighScore m_scores;

};

#endif // TOWER_DEFENCE_SRC_WINDOW_HPP

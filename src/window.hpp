#ifndef TOWER_DEFENCE_SRC_WINDOW_HPP
#define	TOWER_DEFENCE_SRC_WINDOW_HPP

#include "menuObjects.hpp"
#include "map.hpp"
#include "game.hpp"
#include "Towers.hpp"
#include <SFML/Window.hpp>
#include <cstddef>

class Window : public sf::RenderWindow
{
public:
	Window(std::string title, map::Map *map, Game *game);

	~Window();

	sf::Vector2f getMousePosition();
	sf::Vector2f getCurrentMapTile();

	void drawAll();

	void createMenus();
	void createButtons();
	void createTexts();
	void createBars();
	
	void createTowerPlacer();
	void updateTowerPlacer();
	void setTowerPlacerRange(float newRange);
	float getTowerPlacerRange();

	bool isCollision();
	bool isInGameArea();

	void checkEvents();
	void buttonPress();
	void buttonRelease();

private:
	Window(const Window&);
	Window& operator=(const Window&);

	map::Map *m_map;
	Game *m_game;

	gui::Menu m_sideMenu;
	gui::Menu m_bottomMenu;
	gui::Menu m_mapMenu;

	gui::NormalButton m_saveButton;
	gui::NormalButton m_playButton;
	gui::NormalButton m_speedButton;
	gui::NormalButton m_mapButton;

	gui::Text m_saveButtonText;
	gui::Text m_playButtonText;
	gui::Text m_speedButtonText;
	gui::Text m_mapButtonText;

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

	sf::RectangleShape m_towerPlacer;
	sf::CircleShape m_towerPlacerRangeArea;
	float m_towerPlacerRange;

        Tower* tower;
};

#endif // TOWER_DEFENCE_SRC_WINDOW_HPP

#ifndef TOWER_DEFENCE_SRC_WINDOW_HPP
#define	TOWER_DEFENCE_SRC_WINDOW_HPP

#include "menuObjects.hpp"
#include "map.hpp"
#include <SFML/Window.hpp>
#include <cstddef>

class Window : public sf::RenderWindow
{
public:
	Window(std::string title, map::Map *map);

	~Window();

	sf::Vector2f getMousePosition();
	sf::Vector2f getCurrentMapTile();

	void drawAll();

	void createMenus();
	void createButtons();
	void createBars();
	void createTowerPlacer();
	void updateTowerPlacer();
	bool isCollision();
	bool isInGameArea();

	void checkEvents();
	void buttonPress();
	void buttonRelease();

private:
	Window(const Window&);
	Window& operator=(const Window&);

	map::Map *m_map;

	gui::Menu m_sideMenu;
	gui::Menu m_bottomMenu;

	gui::NormalButton m_menuButton;
	gui::NormalButton m_playButton;
	gui::NormalButton m_speedButton;
	gui::NormalButton m_mapButton;

	gui::TowerButton m_tower1Button;
	gui::TowerButton m_tower2Button;
	gui::TowerButton m_tower3Button;

	gui::Bar m_textBar;
	gui::Bar m_lifeBar;

	sf::Vector2f m_mousePosition;

	bool m_isTowerBeingBuilt;
	gui::Towers m_towerBeingBuilt;
	sf::RectangleShape m_towerPlacer;
};

#endif // TOWER_DEFENCE_SRC_WINDOW_HPP
#ifndef TOWER_DEFENCE_SRC_WINDOW_HPP
#define	TOWER_DEFENCE_SRC_WINDOW_HPP

#include "menuObjects.hpp"
#include "map.hpp"
#include <SFML/Window.hpp>
#include <cstddef>

class Window : public sf::RenderWindow
{
public:
	Window(std::string title, map::Map const *map);

	~Window();

	sf::Vector2f getMousePosition();

	void drawAll();

	void createMenus();
	void createButtons();
	void createBars();

	void checkEvents();
	void buttonPress();
	void buttonRelease();

private:
	Window(const Window&);
	Window& operator=(const Window&);

	map::Map const *m_map;

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
};

#endif // TOWER_DEFENCE_SRC_WINDOW_HPP
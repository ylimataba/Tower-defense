#include "window.hpp"
#include "menuObjects.hpp"
#include <SFML/Window.hpp>
#include <cstddef>
#include <string>
#include <iostream>

Window::Window(std::string title, map::Map const *map)
	: sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title, sf::Style::Titlebar | sf::Style::Close),
	  m_mousePosition(0, 0),
	  m_map(map)
{
	setVerticalSyncEnabled(true);

	createMenus();
	createButtons();
	createBars();
}

Window::~Window()
{
	// delete all items: menus, buttons, bars

	this->close();
}

sf::Vector2f Window::getMousePosition()
{
    float x = static_cast<float>(sf::Mouse::getPosition((*this)).x);
    float y = static_cast<float>(sf::Mouse::getPosition((*this)).y);

    m_mousePosition.x = x;
    m_mousePosition.y = y;

    return m_mousePosition;
}

void Window::drawAll()
{
	draw(*m_map);

	draw(m_sideMenu);
	draw(m_bottomMenu);

	draw(m_menuButton);
	draw(m_playButton);
	draw(m_speedButton);
	draw(m_mapButton);

	draw(m_tower1Button);
	draw(m_tower2Button);
	draw(m_tower3Button);

	draw(m_textBar);
	draw(m_lifeBar);
}

void Window::createMenus()
{
	m_sideMenu = gui::Menu(SIDE_MENU_SIZE, SIDE_MENU_POSITION, MENU_COLOR);
    m_bottomMenu = gui::Menu(BOTTOM_MENU_SIZE, BOTTOM_MENU_POSITION, MENU_COLOR);
}

void Window::createButtons()
{
    m_menuButton = gui::NormalButton(BASE_BUTTON_SIZE, MENU_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_playButton = gui::NormalButton(BASE_BUTTON_SIZE, PLAY_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_speedButton = gui::NormalButton(BASE_BUTTON_SIZE, SPEED_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_mapButton = gui::NormalButton(BASE_BUTTON_SIZE, MAP_BUTTON_POSITION, BASE_BUTTON_COLOR);

    m_tower1Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_1_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower2Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_2_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower3Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_3_BUTTON_POSITION, TOWER_BUTTON_COLOR);
}

void Window::createBars()
{
    m_textBar = gui::Bar(TEXT_BAR_SIZE, TEXT_BAR_POSITION, TEXT_BAR_COLOR);
    m_lifeBar = gui::Bar(LIFE_BAR_SIZE, LIFE_BAR_POSITION, LIFE_BAR_COLOR);	
}

void Window::checkEvents()
{
	// Process events
	sf::Event event;

	while (pollEvent(event))
	{
	    // Close window: exit
	    if (event.type == sf::Event::Closed)
	        close();

	    if (event.type == sf::Event::KeyPressed)
	    {
	        switch (event.key.code)
	        {
	            // Escape key: exit
	            case sf::Keyboard::Escape:
	                close();
	                break;

	            default:
	                break;
	        }
	    }

	    // Mouse
	    if (event.type == sf::Event::MouseButtonPressed)
	    {
	        buttonPress();
	    }
	    else if (event.type == sf::Event::MouseButtonReleased)
	    {
	        buttonRelease();
	    }
	    
	}
}

void Window::buttonPress()
{
	getMousePosition();
	//std::cout << "Mouse position: " << m_mousePosition.x << ", " << m_mousePosition.y << std::endl;

	if (m_menuButton.contains(m_mousePosition))
	{
		m_menuButton.buttonPress();
	}
	else if (m_playButton.contains(m_mousePosition))
	{
		m_playButton.buttonPress();
	}
	else if (m_speedButton.contains(m_mousePosition))
	{
		m_speedButton.buttonPress();
	}
	else if (m_mapButton.contains(m_mousePosition))
	{
		m_mapButton.buttonPress();
	}
	else if (m_tower1Button.contains(m_mousePosition))
	{
		m_tower1Button.buttonPress();
	}
	else if (m_tower2Button.contains(m_mousePosition))
	{
		m_tower2Button.buttonPress();
	}
	else if (m_tower3Button.contains(m_mousePosition))
	{
		m_tower3Button.buttonPress();
	}
}

void Window::buttonRelease()
{
	m_menuButton.buttonUnPress();
	m_playButton.buttonUnPress();
	m_speedButton.buttonUnPress();
	m_mapButton.buttonUnPress();

	m_tower1Button.buttonUnPress();
	m_tower2Button.buttonUnPress();
	m_tower3Button.buttonUnPress();
}

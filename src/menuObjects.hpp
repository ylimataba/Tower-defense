#ifndef TOWER_DEFENCE_DEFENCE_HPP
#define	TOWER_DEFENCE_DEFENCE_HPP

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>

// Window and Menus
static const int SIDE_MENU_SCALER_IN_PROCENTS = 15;
static const int BOTTOM_MENU_SCALER_IN_PROCENTS = 10;
static const int MAP_HEIGHT = 640;
static const int MAP_WIDTH = 960;
static const int MAP_TILE_SIZE = 32;

static const int WINDOW_WIDTH = MAP_WIDTH * (100 + SIDE_MENU_SCALER_IN_PROCENTS) / 100;
static const int WINDOW_HEIGHT = MAP_HEIGHT * (100 + BOTTOM_MENU_SCALER_IN_PROCENTS) / 100;

static const int SIDE_MENU_WIDTH = WINDOW_WIDTH - MAP_WIDTH;
static const int SIDE_MENU_HEIGHT = WINDOW_HEIGHT;
static const sf::Vector2f SIDE_MENU_SIZE(SIDE_MENU_WIDTH, SIDE_MENU_HEIGHT);
static const sf::Vector2f SIDE_MENU_POSITION(WINDOW_WIDTH - SIDE_MENU_WIDTH, 0);
static const int BOTTOM_MENU_WIDTH = WINDOW_WIDTH - SIDE_MENU_WIDTH;
static const int BOTTOM_MENU_HEIGHT = WINDOW_HEIGHT - MAP_HEIGHT;
static const sf::Vector2f BOTTOM_MENU_SIZE(BOTTOM_MENU_WIDTH, BOTTOM_MENU_HEIGHT);
static const sf::Vector2f BOTTOM_MENU_POSITION(0, WINDOW_HEIGHT - BOTTOM_MENU_HEIGHT);

// Buttons
static const int BASE_BUTTON_HEIGHT = SIDE_MENU_HEIGHT * 0.04;
static const int BASE_BUTTON_WIDTH = BASE_BUTTON_HEIGHT * 4;
static const int BASE_BUTTON_SPACE = BASE_BUTTON_HEIGHT / 2;
static const int BASE_BUTTON_X_POSITION = BOTTOM_MENU_WIDTH + ((SIDE_MENU_WIDTH - BASE_BUTTON_WIDTH) / 2);
static const int BASE_BUTTON_Y_POSITION = SIDE_MENU_HEIGHT - BOTTOM_MENU_HEIGHT - BASE_BUTTON_HEIGHT - BASE_BUTTON_SPACE;
static const sf::Vector2f BASE_BUTTON_SIZE(BASE_BUTTON_WIDTH, BASE_BUTTON_HEIGHT);

static const sf::Vector2f MENU_BUTTON_POSITION(BASE_BUTTON_X_POSITION, BASE_BUTTON_Y_POSITION);
static const sf::Vector2f PLAY_BUTTON_POSITION(BASE_BUTTON_X_POSITION, 
                                               BASE_BUTTON_Y_POSITION - 1 * (BASE_BUTTON_HEIGHT + BASE_BUTTON_SPACE));
static const sf::Vector2f SPEED_BUTTON_POSITION(BASE_BUTTON_X_POSITION,
                                                BASE_BUTTON_Y_POSITION - 2 * (BASE_BUTTON_HEIGHT + BASE_BUTTON_SPACE));
static const sf::Vector2f MAP_BUTTON_POSITION(BASE_BUTTON_X_POSITION, 
                                              BASE_BUTTON_Y_POSITION - 3 * (BASE_BUTTON_HEIGHT + BASE_BUTTON_SPACE));

static const int TOWER_BUTTON_HEIGHT = BASE_BUTTON_WIDTH * 0.75;
static const int TOWER_BUTTON_WIDTH = TOWER_BUTTON_HEIGHT;
static const int TOWER_BUTTON_SPACE = TOWER_BUTTON_HEIGHT / 4;
static const int TOWER_BUTTON_X_POSITION = BOTTOM_MENU_WIDTH + ((SIDE_MENU_WIDTH - TOWER_BUTTON_WIDTH) / 2);
static const int TOWER_BUTTON_Y_POSITION = TOWER_BUTTON_SPACE;
static const sf::Vector2f TOWER_BUTTON_SIZE(TOWER_BUTTON_WIDTH, TOWER_BUTTON_HEIGHT);

static const sf::Vector2f TOWER_1_BUTTON_POSITION(TOWER_BUTTON_X_POSITION, TOWER_BUTTON_Y_POSITION);
static const sf::Vector2f TOWER_2_BUTTON_POSITION(TOWER_BUTTON_X_POSITION, 
                                                  TOWER_BUTTON_Y_POSITION + 1 * (TOWER_BUTTON_HEIGHT + TOWER_BUTTON_SPACE));
static const sf::Vector2f TOWER_3_BUTTON_POSITION(TOWER_BUTTON_X_POSITION,
                                                  TOWER_BUTTON_Y_POSITION + 2 * (TOWER_BUTTON_HEIGHT + TOWER_BUTTON_SPACE));

// Bars
static const int BASE_BAR_WIDTH = BOTTOM_MENU_WIDTH * 0.9;
static const int BASE_BAR_X_POSITION = (BOTTOM_MENU_WIDTH - BASE_BAR_WIDTH) / 2;

static const sf::Vector2f TEXT_BAR_SIZE(BASE_BAR_WIDTH, BOTTOM_MENU_HEIGHT * 0.5);
static const sf::Vector2f TEXT_BAR_POSITION(BASE_BAR_X_POSITION, WINDOW_HEIGHT - BOTTOM_MENU_HEIGHT + (BOTTOM_MENU_HEIGHT * 0.2));

static const sf::Vector2f LIFE_BAR_SIZE(BASE_BAR_WIDTH, BOTTOM_MENU_HEIGHT * 0.1);
static const sf::Vector2f LIFE_BAR_POSITION(BASE_BAR_X_POSITION, WINDOW_HEIGHT - (BOTTOM_MENU_HEIGHT * 0.2));

// Colors
static const sf::Color MENU_COLOR(39, 174, 96);
static const sf::Color BASE_BUTTON_COLOR(41, 128, 185);
static const sf::Color TOWER_BUTTON_COLOR(0, 255, 255);
static const sf::Color TEXT_BAR_COLOR(0, 255, 0);
static const sf::Color LIFE_BAR_COLOR(255, 0, 0);

static const sf::Color RED(255, 0, 0);
static const sf::Color GREEN(0, 255, 0);
static const sf::Color BLUE(0, 0, 255);
static const sf::Color YELLOW(255, 255, 0);

namespace gui {

enum Towers
{
	NONE = 0,
	TOWER1 = 1,
	TOWER2 = 2,
	TOWER3 = 3
};

namespace button {

enum Buttons
{
	MENU = 0,
	PLAY = 1,
	PAUSE = 2,
	SPEED = 3,
	TOWER = 4
};

enum State
{
	UNPRESSED = 0,
	PRESSED = 1
};

}; // namespace button

class NormalButton : public sf::RectangleShape
{
public:
	NormalButton() : m_button(button::Buttons::MENU) {}
	NormalButton(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color);

	~NormalButton();

	void color(const sf::Color color);
	void text(const std::string text);
	void position(const sf::Vector2f);

	sf::Vector2f getPosition();

	bool contains(sf::Vector2f mousePosition);

	void buttonPress();
	void buttonUnPress();

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Color m_color;
	
	sf::Text m_text;

	button::State m_state;
	button::Buttons m_button;
};

class TowerButton : public sf::RectangleShape
{
public:
	TowerButton() : m_button(button::Buttons::TOWER) {}
	TowerButton(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color);

	~TowerButton();

	void color(const sf::Color color);
	void position(const sf::Vector2f);

	sf::Vector2f getPosition();

	bool contains(sf::Vector2f mousePosition);

	void buttonPress();
	void buttonUnPress();

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Color m_color;

	button::Buttons m_button;
	std::string m_text;
	sf::Font m_font;
	button::State m_state;
};

class Bar : public sf::RectangleShape
{
public:
	Bar() {}
	Bar(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color);

	~Bar();

	void color(const sf::Color color);
	void position(const sf::Vector2f);

	void setHealth(const float newHealth);
	float getHealth();

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Color m_color;

	float m_lengthInPercent;
};

class Menu : public sf::RectangleShape
{
public:
	Menu() {}
	Menu(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color);

	~Menu();

	void color(const sf::Color color);
	void position(const sf::Vector2f);

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Color m_color;
};

}; // namespace gui

#endif // TOWER_DEFENCE_DEFENCE_HPP

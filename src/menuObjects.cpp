#include "menuObjects.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <cstddef>
#include <iostream>

namespace gui {

// NormalButton //

NormalButton::NormalButton(const sf::Vector2f size,
						   const sf::Vector2f position,
						   const sf::Color color)
	: m_button(button::MENU),
	  m_state(button::UNPRESSED),
	  m_size(size),
	  m_position(position),
	  m_color(color)
{
	setSize(size);
	setPosition(position);
	setFillColor(color);
}

NormalButton::~NormalButton()
{

}

void NormalButton::color(sf::Color color)
{
	m_color = color;
	setFillColor(m_color);
}

void NormalButton::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(m_position);
}

sf::Vector2f NormalButton::getPosition()
{
	return m_position;
}

bool NormalButton::contains(sf::Vector2f position)
{
	if ((position.x > m_position.x) && (position.x < (m_position.x + m_size.x) &&
	     position.y > m_position.y) && (position.y < (m_position.y + m_size.y)))
	{
		return true;
	}

	return false;
}

void NormalButton::buttonPress()
{
	color(PRESSED_BASE_BUTTON_COLOR);
}

void NormalButton::buttonUnPress()
{
	color(BASE_BUTTON_COLOR);
}

// TowerButton //

TowerButton::TowerButton(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color)
	: m_button(button::TOWER),
	  m_state(button::UNPRESSED),
	  m_size(size),
	  m_position(position),
	  m_color(color)
{
	setSize(size);
	setPosition(position);
	setFillColor(color);
}

TowerButton::~TowerButton()
{

}

void TowerButton::color(sf::Color color)
{
	m_color = color;
	setFillColor(m_color);
}

void TowerButton::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(m_position);
}

sf::Vector2f TowerButton::getPosition()
{
	return m_position;
}

bool TowerButton::contains(sf::Vector2f mousePosition)
{
	if ((mousePosition.x > m_position.x) && (mousePosition.x < (m_position.x + m_size.x) &&
	     mousePosition.y > m_position.y) && (mousePosition.y < (m_position.y + m_size.y)))
	{
		return true;
	}

	return false;
}

void TowerButton::buttonPress()
{
	color(PRESSED_TOWER_BUTTON_COLOR);
}

void TowerButton::buttonUnPress()
{
	color(TOWER_BUTTON_COLOR);
}

// Bar //

Bar::Bar(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color)
	: m_size(size),
	  m_position(position),
	  m_color(color),
	  m_lengthInPercent(100)
{
	setSize(size);
	setPosition(position);
	setFillColor(color);
}

void Bar::color(sf::Color color)
{
	m_color = color;
	setFillColor(color);
}

void Bar::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(position);
}

sf::Vector2f Bar::getPosition()
{
	return m_position;
}

Bar::~Bar()
{

}

void Bar::setHealth(const float newHealth)
{
	if (newHealth <= 0)
	{
		return;
	}

	m_lengthInPercent = newHealth;

	m_size.x = BASE_BAR_WIDTH / 100 * m_lengthInPercent;
	setSize(m_size);
}

float Bar::getHealth()
{
	return m_lengthInPercent;
}

// Menus //

Menu::Menu(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color)
	: m_size(size),
	  m_position(position),
	  m_color(color)
{
	setSize(size);
	setPosition(position);
	setFillColor(color);
}

Menu::~Menu()
{

}

void Menu::color(sf::Color color)
{
	m_color = color;
	setFillColor(color);
}

void Menu::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(position);
}

// Text //

Text::Text(std::string string, sf::Font& font, sf::RectangleShape* master)
	: m_currentText(string)
{
    setString(m_currentText);
    setFont(font);
    setStyle(sf::Text::Bold);
	setCharacterSize(master->getSize().y * .75);

	float masterOriginX = master->getPosition().x + (master->getSize().x / 2);
	float masterOriginY = master->getPosition().y;
	m_position = sf::Vector2f(masterOriginX, masterOriginY);
	
	refreshPosition();
}

Text::~Text()
{

}

std::string Text::getCurrentText()
{
	return m_currentText;
}

void Text::setText(std::string newText)
{
	m_currentText = newText;
	setString(m_currentText);

	refreshPosition();
}

void Text::refreshPosition()
{
	setPosition(m_position);

	float textOriginX = getLocalBounds().width / 2;
	setOrigin(textOriginX, 0);	
}

} // namespace gui

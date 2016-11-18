#include "menuObjects.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <cstddef>

#include <iostream>

namespace gui {

// NormalButton //

NormalButton::NormalButton(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color)
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
	setFillColor(color);
}

void NormalButton::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(position);
}

sf::Vector2f NormalButton::getPosition()
{
	return m_position;
}

bool NormalButton::contains(sf::Vector2f mousePosition)
{
	if ((mousePosition.x > m_position.x) && (mousePosition.x < (m_position.x + m_size.x) &&
	     mousePosition.y > m_position.y) && (mousePosition.y < (m_position.y + m_size.y)))
	{
		return true;
	}

	return false;
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
	setFillColor(color);
}

void TowerButton::position(sf::Vector2f position)
{
	m_position = position;
	setPosition(position);
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

// Bar //

Bar::Bar(const sf::Vector2f size, const sf::Vector2f position, const sf::Color color)
	: m_size(size),
	  m_position(position),
	  m_color(color)
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
Bar::~Bar()
{

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

Menu::~Menu()
{

}

} // namespace gui
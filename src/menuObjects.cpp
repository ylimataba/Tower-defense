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

void TowerButton::loadTexture(std::string textureName)
{
	m_texture.loadFromFile("../maps/" + textureName + ".png");
	sf::Texture* texture = &m_texture;
	this->setTexture(texture);
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

void Menu::loadTexture(int mapNumber)
{
	m_texture.loadFromFile("../maps/map_" + std::to_string(mapNumber) + ".png");
	sf::Texture* texture = &m_texture;
	this->setTexture(texture);
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

/*--------- TOWERMENU ---------*/
TowerMenu::TowerMenu(sf::Font* font, Game* game) : game(game), font(font){}

bool TowerMenu::contains(sf::Vector2f mousePosition, sf::Vector2f tile){
    if ((upgradeButton.contains(mousePosition) || sellButton.contains(mousePosition) || rangeButton.contains(mousePosition)) && game->getIsBuildPhase() && show)
        return true;
    else if (game->isTower(tile)){
        tower = game->getTower(tile);
        if (game->getIsBuildPhase())
            toggle();
        return true;
    }
    else{
        untoggle();
        return false;
    }
}

void TowerMenu::action(sf::Vector2f mousePosition){
    if(game->getIsBuildPhase() && tower != nullptr){
        if(upgradeButton.contains(mousePosition)){
            std::cout << "upgrade" << tower->get_type() << std::endl;
            game->upgradeTower(tower);
            /* TODO
             * insert here a function call for tower upgrade
             * and remove the print after you're done
             */
            untoggle();
        }
        else if(sellButton.contains(mousePosition)){
            game->sellTower(tower->getPos());
            untoggle();
        }
        else if(rangeButton.contains(mousePosition)){
            tower->toggleRange();
            untoggle();
        }
    }
    else if(tower != nullptr)
        tower->toggleRange();
}

void TowerMenu::toggle(){
    show = true;
    setPosition(tower->getPos());
}

void TowerMenu::untoggle(){
    this->tower = nullptr;
    show = false;
    upgradeButton = NormalButton();
    upgradeText = Text();
    sellButton = NormalButton();
    sellText = Text();
}

void TowerMenu::setPosition(sf::Vector2f position){
    sf::Vector2f delta(34,0);
    sf::Vector2f upgradePosition = position + delta;
    sf::Vector2f deltaSell(0, 32);
    sf::Vector2f deltaRange(0, 64);
    float xlimit = 960 - BASE_BUTTON_WIDTH;
    float ylimit = 640 - 64 - BASE_BUTTON_HEIGHT;
    if(upgradePosition.y > ylimit)
        upgradePosition.y = ylimit;
    if(upgradePosition.x > xlimit)
        upgradePosition.x -= delta.x + BASE_BUTTON_WIDTH ;
    upgradeButton = NormalButton(BASE_BUTTON_SIZE, upgradePosition, BASE_BUTTON_COLOR);
    sellButton = NormalButton(BASE_BUTTON_SIZE, upgradePosition + deltaSell, BASE_BUTTON_COLOR);
    rangeButton = NormalButton(BASE_BUTTON_SIZE, upgradePosition + deltaRange, BASE_BUTTON_COLOR);
    upgradeText = Text("UPGRADE", *font, &upgradeButton);
    sellText = Text("SELL", *font, &sellButton);
    rangeText = Text("RANGE", *font, &rangeButton);
}

void TowerMenu::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    if(show && game->getIsBuildPhase()){
        rt.draw(upgradeButton);
        rt.draw(upgradeText);
        rt.draw(sellButton);
        rt.draw(sellText);
        rt.draw(rangeButton);
        rt.draw(rangeText);
    }
}





} // namespace gui

#include "window.hpp"
#include "menuObjects.hpp"
#include <SFML/Window.hpp>
#include <cstddef>
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>

sf::Font getFont()
{
    sf::Font font;
    font.loadFromFile("../Calibri.ttf");
    return font;
}

sf::Font gameFont(getFont());

Window::Window(std::string title, map::Map *map, Game *game)
	: sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title, sf::Style::Titlebar | sf::Style::Close),
          m_mousePosition(0, 0),
          m_map(map),
          m_game(game),
          m_isTowerBeingBuilt(false),
          m_towerBeingBuilt(gui::NONE),
          m_towerPlacerRange(100),
          m_isMapBeingSelected(false),
          m_currentMapNumber(1)
{
    //setVerticalSyncEnabled(true);

    createMenus();
    createButtons();
    createBars();
    createTexts();
    createTowerPlacer();
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

sf::Vector2f Window::getCurrentMapTile()
{
    getMousePosition();

    float tileX = int(m_mousePosition.x / MAP_TILE_SIZE) * MAP_TILE_SIZE;
    float tileY = int(m_mousePosition.y / MAP_TILE_SIZE) * MAP_TILE_SIZE;

    return sf::Vector2f(tileX, tileY);
}

void Window::drawAll()
{
    clear();

    // TODO Create a container for all drawable objects

    draw(*m_map);

    draw(m_sideMenu);
    draw(m_bottomMenu);

    draw(m_saveButton);
    draw(m_saveButtonText);
    draw(m_playButton);
    draw(m_playButtonText);
    draw(m_speedButton);
    draw(m_speedButtonText);
    draw(m_mapButton);
    draw(m_mapButtonText);

    draw(m_tower1Button);
    draw(m_tower2Button);
    draw(m_tower3Button);
    draw(m_tower4Button);

    draw(m_textBar);
    draw(m_textBarText);
    draw(m_lifeBar);

    //draw(m_towerPlacerRangeArea);
    //draw(m_towerPlacer);
    if (tower != nullptr && m_isTowerBeingBuilt && isInGameArea() && !isCollision())
        draw(*tower);
    
    draw(*m_game);

    draw(m_mapMenu);
}

void Window::createMenus()
{
    m_sideMenu = gui::Menu(SIDE_MENU_SIZE, SIDE_MENU_POSITION, MENU_COLOR);
    m_bottomMenu = gui::Menu(BOTTOM_MENU_SIZE, BOTTOM_MENU_POSITION, MENU_COLOR);
    m_mapMenu = gui::Menu(MAP_MENU_SIZE, MAP_MENU_POSITION, TRANSPARENT);

    m_mapMenu.setOutlineColor(TRANSPARENT);
    m_mapMenu.setOutlineThickness(5);

    m_mapMenu.loadTexture(1);
}

void Window::createButtons()
{
    m_saveButton = gui::NormalButton(BASE_BUTTON_SIZE, SAVE_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_playButton = gui::NormalButton(BASE_BUTTON_SIZE, PLAY_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_speedButton = gui::NormalButton(BASE_BUTTON_SIZE, SPEED_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_mapButton = gui::NormalButton(BASE_BUTTON_SIZE, MAP_BUTTON_POSITION, BASE_BUTTON_COLOR);

    m_tower1Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_1_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower2Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_2_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower3Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_3_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower4Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_4_BUTTON_POSITION, TOWER_BUTTON_COLOR);
}

void Window::createTexts()
{
    m_saveButtonText = gui::Text("SAVE", gameFont, &m_saveButton);
    m_playButtonText = gui::Text("PLAY", gameFont, &m_playButton);
    m_speedButtonText = gui::Text("SPEED", gameFont, &m_speedButton);
    m_mapButtonText = gui::Text("MAPS", gameFont, &m_mapButton);

    m_textBarText = gui::Text("This is the information bar for the game", gameFont, &m_textBar);
}

void Window::createBars()
{
    m_textBar = gui::Bar(TEXT_BAR_SIZE, TEXT_BAR_POSITION, TEXT_BAR_COLOR);
    m_lifeBar = gui::Bar(LIFE_BAR_SIZE, LIFE_BAR_POSITION, LIFE_BAR_COLOR);	
}

void Window::createTowerPlacer()
{
    const sf::Vector2f sizeOfNewTower(MAP_TILE_SIZE, MAP_TILE_SIZE);
    m_towerPlacer = sf::RectangleShape(sizeOfNewTower);
    m_towerPlacer.setFillColor(sf::Color(200, 0, 0, 0));

    m_towerPlacerRangeArea = sf::CircleShape(m_towerPlacerRange);
    m_towerPlacerRangeArea.setFillColor(sf::Color(255, 255, 255, 0));
}

void Window::updateTowerPlacer()
{
    if(tower != nullptr)
        tower->setPosition(getCurrentMapTile());
}

bool Window::isCollision()
{
    sf::Vector2f currentTilePosition = getCurrentMapTile();

    std::vector<sf::Vector2f> collisionPoints;
    collisionPoints.push_back(currentTilePosition);
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x + MAP_TILE_SIZE - 1, currentTilePosition.y + MAP_TILE_SIZE - 1));
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x + MAP_TILE_SIZE - 1, currentTilePosition.y));
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x, currentTilePosition.y + MAP_TILE_SIZE - 1));

    return m_map->isCollision(collisionPoints);
}

bool Window::isInGameArea()
{
    getMousePosition();

    if ((m_mousePosition.x > 0) && (m_mousePosition.x < MAP_WIDTH) &&
        (m_mousePosition.y > 0) && (m_mousePosition.y < MAP_HEIGHT))
    {
        return true;
    }

    return false;
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
                case sf::Keyboard::Escape:
                    if (m_isTowerBeingBuilt)
                    {
                            m_towerBeingBuilt = gui::NONE;
                            m_isTowerBeingBuilt = false;	
                    }

                    break;
                case sf::Keyboard::Right:
                    if (m_isMapBeingSelected)
                    {
                        int nextMapNumber = m_selectedMapNumber + 1;
                        
                        if (nextMapNumber > m_map->getNumberOfMaps())
                        {
                            nextMapNumber = 1;
                        }

                        m_selectedMapNumber = nextMapNumber;
                        m_mapMenu.loadTexture(nextMapNumber);
                        m_textBarText.setText("Level " + std::to_string(nextMapNumber) + " selected");
                    }
                    break;
                case sf::Keyboard::Left:
                    if (m_isMapBeingSelected)
                    {
                        int nextMapNumber = m_selectedMapNumber - 1;

                        if (nextMapNumber < 1)
                        {
                            nextMapNumber = m_map->getNumberOfMaps();
                        }

                        m_selectedMapNumber = nextMapNumber;
                        m_mapMenu.loadTexture(nextMapNumber);
                        m_textBarText.setText("Level " + std::to_string(nextMapNumber) + " selected");
                    }
                    break;
                default:
                    break;
            }
        }

        // Mouse
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (m_isTowerBeingBuilt && !isCollision() && isInGameArea())
            {
                sf::Vector2f tile = getCurrentMapTile();
                std::string text = "@" + std::to_string(int(tile.x)) + "," + std::to_string(int(tile.y));

                switch (m_towerBeingBuilt)//1=Basic, 2=Freeze, 3=Precision, 4=Blast
                {
                    case gui::TOWER1:
                        text = "Tower 1 placed on map " + text; 
                        m_game->addTower(tower);
                        tower = nullptr;
                        break;
                    case gui::TOWER2:
                        text = "Tower 2 placed on map " + text;
                        m_game->addTower(tower);
                        tower = nullptr;
                        break;
                    case gui::TOWER3:
                        text = "Tower 3 placed on map " + text;
                        m_game->addTower(tower);
                        tower = nullptr;
                        break;
                    case gui::TOWER4:
                        text = "Tower 4 placed on map " + text;
                        m_game->addTower(tower);
                        tower = nullptr;
                        break;
                    case gui::NONE:
                    default:
                        text = "";
                        break;
                }

                m_textBarText.setText(text);
                m_towerBeingBuilt = gui::NONE;
                m_isTowerBeingBuilt = false;
            }
            else if(m_game->isTower(getCurrentMapTile())){
                auto tower = m_game->getTower(getCurrentMapTile());
                tower->toggleRange();
            }

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

    if (m_saveButton.contains(m_mousePosition))
    {
        m_saveButton.buttonPress();
    }
    else if (m_playButton.contains(m_mousePosition))
    {
        if (m_game->getIsBuildPhase() && !(m_game->getIsGamePaused()))
        {
            m_textBarText.setText("Game started");
            m_playButtonText.setText("PAUSE");
            m_game->setIsBuildPhase(false);
        }
        else if (!(m_game->getIsGamePaused()))
        {
            m_textBarText.setText("Game paused");
            m_playButtonText.setText("RESUME");
            m_game->setIsGamePaused(true);
        }
        else
        {
            m_textBarText.setText("Game resumed");
            m_playButtonText.setText("PAUSE");
            m_game->setIsGamePaused(false);
        }

        m_playButton.buttonPress();
    }
    else if (m_speedButton.contains(m_mousePosition))
    {
        std::string speedButtonText = "SPEED";
        int currentGameSpeed = m_game->getSpeed();
        int newGameSpeed = 1;

        if (currentGameSpeed < 4)
        {
            newGameSpeed =  currentGameSpeed * 2;
            speedButtonText = std::to_string(newGameSpeed) + "x";
        }

        m_textBarText.setText("Game speed x" + std::to_string(newGameSpeed));
        m_game->setSpeed(newGameSpeed);
        m_speedButtonText.setText(speedButtonText);
        m_speedButton.buttonPress();
    }
    else if (m_mapButton.contains(m_mousePosition))
    {
        if (m_game->getIsGamePaused())
        {
            m_textBarText.setText("Map selection");
            m_game->setIsGamePaused(false);
            m_mapMenu.color(TRANSPARENT);
            m_mapMenu.setOutlineColor(TRANSPARENT);
            m_isMapBeingSelected = false;
        }
        else
        {
            m_game->setIsGamePaused(true);
            m_mapMenu.color(MAP_MENU_COLOR);
            m_mapMenu.setOutlineColor(BASE_BUTTON_COLOR);
            m_isMapBeingSelected = true;
        }
        m_mapButton.buttonPress();
    }
    else if (m_tower1Button.contains(m_mousePosition))
    {
        if (m_game->getIsBuildPhase())
        {
            m_isTowerBeingBuilt = true;
            tower = new BasicTower();
            m_towerBeingBuilt = gui::TOWER1;
            m_tower1Button.buttonPress();
        }
    }
    else if (m_tower2Button.contains(m_mousePosition))
    {
        if (m_game->getIsBuildPhase())
        {
            m_isTowerBeingBuilt = true;
            tower = new FreezeTower();
            m_towerBeingBuilt = gui::TOWER2;
            m_tower2Button.buttonPress();
        }
    }
    else if (m_tower3Button.contains(m_mousePosition))
    {
        if (m_game->getIsBuildPhase())
        {
            m_isTowerBeingBuilt = true;
            tower = new PrecisionTower();
            m_towerBeingBuilt = gui::TOWER3;
            m_tower3Button.buttonPress();			
        }
    }
    else if (m_tower4Button.contains(m_mousePosition))
    {
        if (m_game->getIsBuildPhase())
        {
            m_isTowerBeingBuilt = true;
            tower = new BlastTower();
            m_towerBeingBuilt = gui::TOWER4;
            m_tower4Button.buttonPress();
        }
    }
}

void Window::buttonRelease()
{
    m_saveButton.buttonUnPress();
    m_playButton.buttonUnPress();
    m_speedButton.buttonUnPress();
    m_mapButton.buttonUnPress();

    m_tower1Button.buttonUnPress();
    m_tower2Button.buttonUnPress();
    m_tower3Button.buttonUnPress();
    m_tower4Button.buttonUnPress();
}

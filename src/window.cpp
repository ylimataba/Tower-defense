#include "window.hpp"
#include "menuObjects.hpp"
#include "save.hpp"
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

Window::Window(std::string title, Game *game) :
    sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title, sf::Style::Titlebar | sf::Style::Close),
    m_mousePosition(0, 0),
    m_game(game),
    m_isTowerBeingBuilt(false),
    m_towerBeingBuilt(gui::NONE),
    m_isMapBeingSelected(false),
    m_currentMapNumber(1)
{
    createMenus();
    createButtons();
    createBars();
    createTexts();

    m_scores = HighScore(&gameFont, game);
}

Window::~Window()
{
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

    if(tileY > (MAP_HEIGHT - MAP_TILE_SIZE))
    {
        tileY = (MAP_HEIGHT - MAP_TILE_SIZE);
    }

    if(tileX > (MAP_WIDTH - MAP_TILE_SIZE))
    {
        tileX = (MAP_WIDTH - MAP_TILE_SIZE);
    }

    if(tileY < 0)
    {
        tileY = 0;
    }

    if(tileX < 0)
    {
        tileX = 0;
    }

    return sf::Vector2f(tileX, tileY);
}

void Window::drawAll()
{
    clear();

    if (m_game->getIsGameOver())
    {
        m_playButtonText.setText("NEW GAME");
    }
    else if (m_game->getIsBuildPhase())
    {   // Set text back to play between rounds
        m_playButtonText.setText("PLAY");
    }

    draw(*m_game);
    
    draw(m_sideMenu);
    draw(m_bottomMenu);

    draw(m_saveButton);
    draw(m_playButton);
    draw(m_speedButton);
    draw(m_mapButton);
    draw(m_loadButton);
    draw(m_scoresButton);

    draw(m_tower1Button);
    draw(m_tower2Button);
    draw(m_tower3Button);
    draw(m_tower4Button);

    draw(m_textBar);

    m_lifeBar.setHealth(m_game->getHealth());
    draw(m_lifeBar);
    
    draw(m_loadButtonText);
    draw(m_saveButtonText);
    draw(m_playButtonText);
    draw(m_speedButtonText);
    draw(m_mapButtonText);
    draw(m_scoresButtonText);

    draw(m_textBarText);

    if (m_tower != nullptr && m_isTowerBeingBuilt && !isCollision())
    {
        draw(*m_tower);
    }

    draw(m_towerMenu);
    
    draw(m_mapMenu);

    draw(m_scores);
}

void Window::createMenus()
{
    m_sideMenu = gui::Menu(SIDE_MENU_SIZE, SIDE_MENU_POSITION, MENU_COLOR);
    m_bottomMenu = gui::Menu(BOTTOM_MENU_SIZE, BOTTOM_MENU_POSITION, MENU_COLOR);

    m_mapMenu = gui::Menu(MAP_MENU_SIZE, MAP_MENU_POSITION, TRANSPARENT);
    m_mapMenu.setOutlineColor(TRANSPARENT);
    m_mapMenu.setOutlineThickness(5);
    m_mapMenu.loadTexture(1);

    m_towerMenu = gui::TowerMenu(&gameFont, m_game);
}

void Window::createButtons()
{
    m_saveButton = gui::NormalButton(BASE_BUTTON_SIZE, SAVE_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_playButton = gui::NormalButton(BASE_BUTTON_SIZE, PLAY_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_speedButton = gui::NormalButton(BASE_BUTTON_SIZE, SPEED_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_mapButton = gui::NormalButton(BASE_BUTTON_SIZE, MAP_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_loadButton = gui::NormalButton(BASE_BUTTON_SIZE, LOAD_BUTTON_POSITION, BASE_BUTTON_COLOR);
    m_scoresButton = gui::NormalButton(BASE_BUTTON_SIZE, SCORES_BUTTON_POSITION, BASE_BUTTON_COLOR);

    m_tower1Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_1_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower2Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_2_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower3Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_3_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    m_tower4Button = gui::TowerButton(TOWER_BUTTON_SIZE, TOWER_4_BUTTON_POSITION, TOWER_BUTTON_COLOR);

    m_tower1Button.loadTexture("Basic");
    m_tower2Button.loadTexture("Freeze");
    m_tower3Button.loadTexture("Precision");
    m_tower4Button.loadTexture("Blast");
}

void Window::createTexts()
{
    m_saveButtonText = gui::Text("SAVE", gameFont, &m_saveButton);
    m_playButtonText = gui::Text("PLAY", gameFont, &m_playButton);
    m_speedButtonText = gui::Text("SPEED", gameFont, &m_speedButton);
    m_mapButtonText = gui::Text("MAPS", gameFont, &m_mapButton);
    m_loadButtonText = gui::Text("LOAD", gameFont, &m_loadButton);
    m_scoresButtonText = gui::Text("SCORES", gameFont, &m_scoresButton);

    m_textBarText = gui::Text("New game", gameFont, &m_textBar);
}

void Window::createBars()
{
    m_textBar = gui::Bar(TEXT_BAR_SIZE, TEXT_BAR_POSITION, TEXT_BAR_COLOR);
    m_lifeBar = gui::Bar(LIFE_BAR_SIZE, LIFE_BAR_POSITION, LIFE_BAR_COLOR);	
}


void Window::updateTowerPlacer()
{
    if(m_tower != nullptr)
    {
        sf::Vector2f position = getCurrentMapTile();

        m_tower->setPosition(position);
    }
}

bool Window::isCollision()
{
    sf::Vector2f currentTilePosition = getCurrentMapTile();

    std::vector<sf::Vector2f> collisionPoints;
    collisionPoints.push_back(currentTilePosition);
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x + MAP_TILE_SIZE - 1, currentTilePosition.y + MAP_TILE_SIZE - 1));
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x + MAP_TILE_SIZE - 1, currentTilePosition.y));
    collisionPoints.push_back(sf::Vector2f(currentTilePosition.x, currentTilePosition.y + MAP_TILE_SIZE - 1));

    return m_game->getMap()->isCollision(collisionPoints);
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
    sf::Event event;

    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)	
        {    	
            close();
        }

        if (m_game->getIsGameOver()){
            m_scores.getUsername(event);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    if (m_isTowerBeingBuilt)
                    {
                        m_towerBeingBuilt = gui::NONE;
                        m_isTowerBeingBuilt = false;	
                        m_textBarText.setText("");
                        if (m_tower != nullptr)
                        {
                            delete m_tower;
                            m_tower = nullptr;
                        }
                    }
                    else if (m_isMapBeingSelected)
                    {
                        m_mapMenu.color(TRANSPARENT);
                        m_mapMenu.setOutlineColor(TRANSPARENT);
                        m_isMapBeingSelected = false;
                        m_textBarText.setText("");
                    }
                    break;

                case sf::Keyboard::Right:
                    if (m_isMapBeingSelected)
                    {
                        int nextMapNumber = m_selectedMapNumber + 1;
                        
                        if (nextMapNumber > m_game->getNumberOfMaps())
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
                            nextMapNumber = m_game->getNumberOfMaps();
                        }

                        m_selectedMapNumber = nextMapNumber;
                        m_mapMenu.loadTexture(nextMapNumber);
                        m_textBarText.setText("Level " + std::to_string(nextMapNumber) + " selected");
                    }
                    break;

                case sf::Keyboard::Return:
                    if (m_isMapBeingSelected)
                    {
                        if (m_selectedMapNumber <= m_currentMapNumber)
                        {
                            m_textBarText.setText("Changin map");

                            m_mapMenu.color(TRANSPARENT);
                            m_mapMenu.setOutlineColor(TRANSPARENT);
                            m_isMapBeingSelected = false;

                            // TODO Load new map and game (with round specific cash etc)
                            m_game->reset();
                            m_game->setNextMap("map_" + std::to_string(m_selectedMapNumber) + ".tmx");

                            break;
                        }

                        m_textBarText.setText("Map selected is not unlocked");
                    }
                    break;

                default:
                    break;
            }
        }

        // Mouse
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                m_isTowerBeingBuilt = false;

                if (m_tower != nullptr)
                {
                    delete m_tower;
                    m_tower = nullptr;
                    m_textBarText.setText("");
                }
            }
            else if (m_isTowerBeingBuilt && !isCollision() && isInGameArea())
            {
                sf::Vector2f tile = getCurrentMapTile();

                std::string text;

                switch (m_towerBeingBuilt)//1=Basic, 2=Freeze, 3=Precision, 4=Blast
                {
                    case gui::TOWER:
                        text = "Tower placed on map "; 
                        m_game->addTower(m_tower);
                        m_tower = nullptr;
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
            else 
            {
                    buttonPress();
            }
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

    if(!m_isTowerBeingBuilt)
    {
        if (m_saveButton.contains(m_mousePosition) && (m_game->getIsBuildPhase() || m_game->getIsGameOver()))
        {
            m_game->setIsGamePaused(true);

            save::Save *newSave = new save::Save(m_game->getObjectsToSave());
            newSave->saveGame();
            delete newSave;

            m_textBarText.setText("Game saved");
            m_saveButton.buttonPress();
        }
        else if (m_loadButton.contains(m_mousePosition) && (m_game->getIsBuildPhase() || m_game->getIsGameOver()))
        {
            std::string str = "";

            m_game->setIsGamePaused(true);

            m_game->loadObjects();

            m_textBarText.setText(str);            
            m_loadButton.buttonPress();
        }
        else if (m_playButton.contains(m_mousePosition))
        {
            if (m_game->getIsGameOver())
            {
                m_scores.hideScores();
                m_game->reset();
            }
            else if (m_game->getIsBuildPhase())
            {
                m_textBarText.setText("Game started");
                m_playButtonText.setText("PAUSE");
                m_game->setIsBuildPhase(false);
                m_scores.hideScores();
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
                m_scores.hideScores();
            }

            m_playButton.buttonPress();
        }
        else if (m_speedButton.contains(m_mousePosition) && (!m_game->getIsGamePaused() && !m_game->getIsBuildPhase()) && !m_game->getIsGameOver())
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
            if (m_game->getIsGamePaused() && m_isMapBeingSelected)
            {
                m_mapMenu.color(TRANSPARENT);
                m_mapMenu.setOutlineColor(TRANSPARENT);
                m_isMapBeingSelected = false;
            }
            else
            {
                m_game->setIsGamePaused(true);
                m_playButtonText.setText("RESUME");

                std::string mapName = m_game->getMap()->getMapName();
                m_selectedMapNumber = std::stoi(mapName.substr(mapName.length() - 5, 1));

                m_textBarText.setText("Map selection");
                m_mapMenu.color(MAP_MENU_COLOR);
                m_mapMenu.setOutlineColor(BASE_BUTTON_COLOR);
                m_isMapBeingSelected = true;
            }

            m_mapButton.buttonPress();
        }
        else if(m_scoresButton.contains(m_mousePosition) && (m_game->getIsBuildPhase() || m_game->getIsGameOver()))
        {
            if(m_scores.isShowing())
                m_scores.hideScores();
            else
                m_scores.showScores();
            m_scoresButton.buttonPress();
        }
        else if (m_tower1Button.contains(m_mousePosition) && !m_game->getIsGameOver())
        {
            if (m_game->getIsBuildPhase())
            {
                m_tower = new BasicTower();

                if(m_game->getMoney() >= m_tower->get_cost())
                {
                    m_textBarText.setText("Left click to set tower on map. Right click to cancel.");
                    m_isTowerBeingBuilt = true;
                    m_towerBeingBuilt = gui::TOWER;
                    m_tower1Button.buttonPress();
                }
                else
                {
                    delete m_tower;
                    m_tower = nullptr;
                    m_isTowerBeingBuilt = false;
                }
            }
        }
        else if (m_tower2Button.contains(m_mousePosition) && !m_game->getIsGameOver())
        {
            if (m_game->getIsBuildPhase())
            {
                m_tower = new FreezeTower();

                if(m_game->getMoney() >= m_tower->get_cost())
                {
                    m_textBarText.setText("Left click to set tower on map. Right click to cancel.");
                    m_isTowerBeingBuilt = true;
                    m_towerBeingBuilt = gui::TOWER;
                    m_tower2Button.buttonPress();
                }
                else
                {
                    delete m_tower;
                    m_tower = nullptr;
                    m_isTowerBeingBuilt = false;
                }
            }
        }
        else if (m_tower3Button.contains(m_mousePosition) && !m_game->getIsGameOver())
        {
            if (m_game->getIsBuildPhase())
            {
                m_tower = new PrecisionTower();

                if(m_game->getMoney() >= m_tower->get_cost())
                {
                    m_textBarText.setText("Left click to set tower on map. Right click to cancel.");
                    m_isTowerBeingBuilt = true;
                    m_towerBeingBuilt = gui::TOWER;
                    m_tower3Button.buttonPress();
                }
                else
                {
                    delete m_tower;
                    m_tower = nullptr;
                    m_isTowerBeingBuilt = false;
                }
            }
        }
        else if (m_tower4Button.contains(m_mousePosition) && !m_game->getIsGameOver())
        {
            if (m_game->getIsBuildPhase())
            {
                m_tower = new BlastTower();

                if(m_game->getMoney() >= m_tower->get_cost())
                {
                    m_textBarText.setText("Left click to set tower on map. Right click to cancel.");
                    m_isTowerBeingBuilt = true;
                    m_towerBeingBuilt = gui::TOWER;
                    m_tower4Button.buttonPress();
                }
                else
                {
                    delete m_tower;
                    m_tower = nullptr;
                    m_isTowerBeingBuilt = false;
                }
            }
        }
        else if (m_towerMenu.contains(m_mousePosition, getCurrentMapTile()) && !m_game->getIsGameOver())
        {
            m_towerMenu.action(m_mousePosition);
        }
    }
}

void Window::buttonRelease()
{
    m_saveButton.buttonUnPress();
    m_playButton.buttonUnPress();
    m_speedButton.buttonUnPress();
    m_mapButton.buttonUnPress();
    m_loadButton.buttonUnPress();
    m_scoresButton.buttonUnPress();

    m_tower1Button.buttonUnPress();
    m_tower2Button.buttonUnPress();
    m_tower3Button.buttonUnPress();
    m_tower4Button.buttonUnPress();
}

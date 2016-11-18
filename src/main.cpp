//#include "tower.hpp"
//#include "enemy.hpp"
#include "menuObjects.hpp"

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

int main()
{
    tmx::MapLoader ml("../maps/");
    ml.Load("map_1.tmx");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower Defence",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true);

    gui::Menu sideMenu(SIDE_MENU_SIZE, SIDE_MENU_POSITION, MENU_COLOR);
    gui::Menu bottomMenu(BOTTOM_MENU_SIZE, BOTTOM_MENU_POSITION, MENU_COLOR);

    // TODO Menus should own all its content
    // Overload the draw to draw its content

    gui::NormalButton menuButton(BASE_BUTTON_SIZE, MENU_BUTTON_POSITION, BASE_BUTTON_COLOR);
    gui::NormalButton playButton(BASE_BUTTON_SIZE, PLAY_BUTTON_POSITION, BASE_BUTTON_COLOR);
    gui::NormalButton speedButton(BASE_BUTTON_SIZE, SPEED_BUTTON_POSITION, BASE_BUTTON_COLOR);
    gui::NormalButton mapButton(BASE_BUTTON_SIZE, MAP_BUTTON_POSITION, BASE_BUTTON_COLOR);

    gui::TowerButton tower1Button(TOWER_BUTTON_SIZE, TOWER_1_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    gui::TowerButton tower2Button(TOWER_BUTTON_SIZE, TOWER_2_BUTTON_POSITION, TOWER_BUTTON_COLOR);
    gui::TowerButton tower3Button(TOWER_BUTTON_SIZE, TOWER_3_BUTTON_POSITION, TOWER_BUTTON_COLOR);

    gui::Bar textBar(TEXT_BAR_SIZE, TEXT_BAR_POSITION, TEXT_BAR_COLOR);
    gui::Bar lifeBar(LIFE_BAR_SIZE, LIFE_BAR_POSITION, LIFE_BAR_COLOR);

    // Create clock and start loop
    sf::Clock clock;
    
    sf::Clock testClock;
    sf::Time testTime = sf::seconds(1);
    // Two loops
    // 1. build phase //DO THIS
    // 2. play phase

    while (window.isOpen())
    {
        if (testClock.getElapsedTime() > testTime)
        {
            lifeBar.setHealth(lifeBar.getHealth() - 1.0);
            testClock.restart();
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    // Escape key: exit
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    default:
                        break;
                }
            }

            // Mouse
            if (event.type == sf::Event::MouseButtonPressed)
            {
                float x = static_cast<float>(sf::Mouse::getPosition(window).x);
                float y = static_cast<float>(sf::Mouse::getPosition(window).y);
                sf::Vector2f mousePosition(x, y);

                if (menuButton.contains(mousePosition))
                {
                    menuButton.buttonPress();
                }
                else if (playButton.contains(mousePosition))
                {
                    playButton.buttonPress();
                }
                else if (speedButton.contains(mousePosition))
                {
                    speedButton.buttonPress();
                }
                else if (mapButton.contains(mousePosition))
                {
                    mapButton.buttonPress();
                }

                if (tower1Button.contains(mousePosition))
                {
                    tower1Button.buttonPress();
                }
                else if (tower2Button.contains(mousePosition))
                {
                    tower2Button.buttonPress();
                }
                else if (tower3Button.contains(mousePosition))
                {
                    tower3Button.buttonPress();
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                menuButton.buttonUnPress();
                playButton.buttonUnPress();
                speedButton.buttonUnPress();
                mapButton.buttonUnPress();

                tower1Button.buttonUnPress();
                tower2Button.buttonUnPress();
                tower3Button.buttonUnPress();
            }
            
        }

        window.clear(sf::Color(255, 255, 255));

        window.draw(ml);
        
        window.draw(sideMenu);
        window.draw(bottomMenu);

        window.draw(menuButton);
        window.draw(playButton);
        window.draw(speedButton);
        window.draw(mapButton);

        window.draw(tower1Button);
        window.draw(tower2Button);
        window.draw(tower3Button);

        window.draw(textBar);
        window.draw(lifeBar);

        // Finally, display the rendered frame on screen
        window.display();
    }

    // delete the effects

    return EXIT_SUCCESS;
}

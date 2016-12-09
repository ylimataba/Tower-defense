#include "game.hpp"

sf::Font font(getFont());

Game::Game(map::Map* map)
    : delayTime(sf::milliseconds(1000 / 60)),
      isBuildPhase(true),
      isGamePaused(false),
      map(map)
{
    health = 100;
    money = 200;

    score.setFont(font);
    score.setPosition(10,600);
    score.setString(std::to_string(points));
    score.setCharacterSize(30);
    score.setStyle(sf::Text::Bold);
    score.setColor(sf::Color::White);
    
    cash.setFont(font);
    cash.setPosition(10,10);
    cash.setString(std::to_string(money));
    cash.setCharacterSize(30);
    cash.setStyle(sf::Text::Bold);
    cash.setColor(sf::Color::Yellow);
}

Game::~Game(){
    for(auto &enemy : enemyList)
        enemy.reset(nullptr);
    for(auto &tower : towerList)
        delete tower;
}

void Game::create_enemies(float timeBetweenSpawn)
{
    if(!isGamePaused)
        if((enemies == 0 || spawnTime.getElapsedTime().asSeconds() * speed > timeBetweenSpawn + enemyPause) && !current_round.empty()){
        if(first_wave == true || (waveDelay.getElapsedTime().asSeconds() * speed > waveDelayTime + enemyPause)) {
            char type = current_round[0];
            switch(type){
                case 'A':
                    enemyList.push_back( std::unique_ptr<Enemy> (new EasyEnemy(map->getEnemyRoute())) );
                    break;
                case 'B':
                    enemyList.push_back( std::unique_ptr<Enemy> (new NormalEnemy(map->getEnemyRoute())) );
                    break;
                case 'C':
                    enemyList.push_back( std::unique_ptr<Enemy> (new HardEnemy(map->getEnemyRoute())) );
                    break;
                case 't':
                    waveDelay.restart();
                    first_wave = false;//inappropriate delay prevention
                    break;
            }
            current_round.erase(current_round.begin());
            enemies++;
            spawnTime.restart();
            enemyPause = 0;
        }
        }
}

void Game::addTower(sf::Vector2f position, int type)
{
    if(isBuildPhase && money > 0){
        switch(type)
        {
            case 1:
              {
                Tower* newTower = new BasicTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                money -= 100;
                cash.setString(std::to_string(money));
                break;
              }
            case 2:
              {
                Tower* newTower = new FreezeTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                money -= 200;
                cash.setString(std::to_string(money));
                break;
              }
            case 3:
              {
                Tower* newTower = new PrecisionTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                money -= 300;
                cash.setString(std::to_string(money));
                break;
              }
            case 4:
              {
                Tower* newTower = new BlastTower(position);
                this->towerList.push_back(newTower);
                map->addTower(position);
                money -= 500;
                cash.setString(std::to_string(money));
                break;
              }
        }
    }
}
bool Game::isTower(sf::Vector2f position){
    auto tower = std::find_if(towerList.begin(), towerList.end(),
            [position](Tower* item)
            { return item->getPos() == position; });
    return tower != towerList.end();
}

Tower* Game::getTower(sf::Vector2f position){
    auto tower = std::find_if(towerList.begin(), towerList.end(),
            [position](Tower* item)
            { return item->getPos() == position; });
    return *tower;
}



void Game::removeTower(std::vector<Tower*>::iterator it)
{
    //map->removeTower(/*topLeftCornerOfTower*/);
    this->towerList.erase(it);
}


void Game::move_enemies()
{
    float deltaTime = moveTime.restart().asSeconds();
    if(!isGamePaused){
        for(auto &enemy : enemyList) 
            if(enemy != nullptr){
                enemy->move(deltaTime, speed);
                if(enemy->is_finished()){
                    health--;
                    enemy.reset();
                }
                else if(!enemy->is_alive())
                    enemy.reset();
            }
        enemyList.erase(remove(enemyList.begin(), enemyList.end(), nullptr), enemyList.end());
    }
}

void Game::shoot_enemies()
{
    if(!isGamePaused)
        for(auto tower : this->towerList)
            points += tower->shoot(enemyList, towerPause, speed);
    score.setString(std::to_string(points));
}

bool Game::round_completed()
{
    if(enemyList.empty() && current_round.empty())
        return true;
    else
        return false;
}

bool Game::next_round()
{
    if(rounds.size() > 1){
        rounds.erase(rounds.begin());
        current_round = rounds[0];
        enemies = 0;
        setIsBuildPhase(true);
        first_wave = true;
        return true;
    }
    return false;
}

void Game::play()
{
    create_enemies(.5f);
    move_enemies(); 
    shoot_enemies();
    if(round_completed())
        next_round();
}

void Game::set_rounds(std::vector<std::string> rounds)
{
    this->rounds = rounds;
    current_round = rounds[0];
}

/*
bool Game::health_ok()
{
    if(this->health > 0)
        return true;
    else
        return false;
}

int Game::getHealth()
{
    return this->health;
}
*/
int Game::getMoney()
{
    return this->money;
}



void Game::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    for(auto &enemy : enemyList)
        if(enemy != nullptr)
            rt.draw(*enemy);
    for(auto tower : towerList)
        rt.draw(*tower);
    rt.draw(score);
    rt.draw(cash);
}

void Game::setIsBuildPhase(bool setPhase)
{
    isBuildPhase = setPhase;
}

bool Game::getIsBuildPhase()
{
    return isBuildPhase;
}

void Game::setIsGamePaused(bool pauseState)
{
    if(!pauseState){
        enemyPause += pauseClock.restart().asSeconds();
        towerPause = enemyPause;
    }
    pauseClock.restart();
    isGamePaused = pauseState;
}

bool Game::getIsGamePaused()
{
    return isGamePaused;
}

sf::Time Game::getDelayTime()
{
    return delayTime;
}

void Game::setSpeed(int speedFactor){
    speed = speedFactor;
}

int Game::getSpeed() const{
    return speed;
}

#include "game.hpp"
#include <iostream>

sf::Font font(getFont());

Game::Game()
    : delayTime(sf::milliseconds(1000 / 60)),
      isBuildPhase(true),
      isGamePaused(false),
      numberOfMaps(2)

{
    setNumerOfMaps();
    map = new map::Map("map_1.tmx");
    gameOver = false;
    playerWon = false;
    health = 100;
    money = 6500;
    round_number = 1;
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

    round.setFont(font);
    round.setPosition(820,10);
    round.setString("Round " + std::to_string(round_number));
    round.setCharacterSize(30);
    round.setStyle(sf::Text::Bold);
    round.setColor(sf::Color::White);


    health_indicator.setFont(font);
    health_indicator.setPosition(10,50);
    health_indicator.setString(std::to_string(health));
    health_indicator.setCharacterSize(30);
    health_indicator.setStyle(sf::Text::Bold);
    health_indicator.setColor(sf::Color::Red);

    game_over.setFont(font);
    game_over.setPosition(200,200);
    game_over.setString("GAME OVER!");
    game_over.setCharacterSize(100);
    game_over.setStyle(sf::Text::Bold);
    game_over.setColor(sf::Color::Red);

    player_won.setFont(font);
    player_won.setPosition(200,200);
    player_won.setString("YOU WON!");
    player_won.setCharacterSize(100);
    player_won.setStyle(sf::Text::Bold);
    player_won.setColor(sf::Color::Blue);

}

Game::~Game(){
    for(auto &enemy : enemyList)
        enemy.reset(nullptr);
    for(auto &tower : towerList)
        delete tower;
    delete map;
}

map::Map* Game::getMap() const{
    return map;
}
void Game::setNextMap(std::string mapName){
    delete map;
    map = new map::Map(mapName);
}

void Game::create_enemies(float timeBetweenSpawn)
{
    if(!isGamePaused)
        if((enemies == 0 || spawnTime.getElapsedTime().asSeconds() * speed > timeBetweenSpawn + enemyPause) && !current_round.empty()){
        if(first_wave == true || (waveDelay.getElapsedTime().asSeconds() * speed > waveDelayTime + enemyPause)) {
            char type = current_round[0];
            switch(type){
                case 'A':
                    enemyList.push_back( std::unique_ptr<Enemy> (new EasyEnemy(map->getEnemyRoute(), enemy_id)) );
                    enemy_id++;
                    break;
                case 'B':
                    enemyList.push_back( std::unique_ptr<Enemy> (new NormalEnemy(map->getEnemyRoute(), enemy_id)) );
                    enemy_id++;
                    break;
                case 'C':
                    enemyList.push_back( std::unique_ptr<Enemy> (new HardEnemy(map->getEnemyRoute(), enemy_id)) );
                    enemy_id++;
                    break;
                case 'D':
                    enemyList.push_back( std::unique_ptr<Enemy> (new ExtremeEnemy(map->getEnemyRoute(), enemy_id)) );
                    enemy_id++;
                    break;
                case 'E':
                    enemyList.push_back( std::unique_ptr<Enemy> (new SuperEnemy(map->getEnemyRoute(), enemy_id)) );
                    enemy_id++;
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

void Game::addTower(Tower* tower)
{
    if(isBuildPhase && money >= tower->get_cost()){
        money -= tower->get_cost();
        tower->toggleRange();
        towerList.push_back(tower);
        cash.setString(std::to_string(money));
        map->addTower(tower->getPos());
    }
    else delete tower;
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

void Game::removeTower(sf::Vector2f position)
{
    map->removeTower(position);
    for_each(towerList.begin(), towerList.end(),
            [position](Tower*& tower)
            { if(tower->getPos() == position){
                delete tower;
                tower = nullptr;
                }
            });
    towerList.erase(remove(towerList.begin(), towerList.end(), nullptr), towerList.end());
}


void Game::move_enemies()
{
    float deltaTime = moveTime.restart().asSeconds();
    if(!isGamePaused){
        for(auto &enemy : enemyList) 
            if(enemy != nullptr){
                enemy->move(deltaTime, speed);
                if(enemy->is_finished()){
                    health -= enemy->get_hp();
                    health_indicator.setString(std::to_string(health));
                    enemy.reset();
                }
                else if(!enemy->is_alive()){
                    money += enemy->get_value();
                    cash.setString(std::to_string(money));
                    enemy.reset();
                }
            }
        enemyList.erase(remove(enemyList.begin(), enemyList.end(), nullptr), enemyList.end());
    }
}

void Game::shoot_enemies()
{
    if(!isGamePaused)
        for(auto tower : this->towerList)
        {
            points += tower->shoot(enemyList, towerPause, speed);
        }
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
    if(rounds.size() > 2){
        rounds.erase(rounds.begin());
        current_round = rounds[0];
        enemies = 0;
        setIsBuildPhase(true);
        first_wave = true;
        enemy_id = 0;
        round_number++;
        return true;
    }

    return false;
}

void Game::play()
{
    if(!gameOver && health_ok()){
        round.setString("Round " + std::to_string(round_number));
        create_enemies(.2f);
        move_enemies(); 
        shoot_enemies();
        if(round_completed())
        {
            addMoney(round_bonus);
            if(!next_round()){
                if(health_ok())
                    playerWon = true;
                gameOver = true;
            }

        }
    }	
}

void Game::set_rounds(std::vector<std::string> rounds)
{
    this->rounds = rounds;
    current_round = rounds[0];
    //round_number = 1;
}


bool Game::health_ok()
{
    if(this->health > 0){
        gameOver = false;
        return true;
    }

    else{
        health = 0;
        health_indicator.setString(std::to_string(health));
        gameOver = true;
        return false;
    }
}

int Game::getHealth()
{
    return this->health;
}

int Game::getMoney()
{
    return this->money;
}

void Game::addMoney(int amount)
{
    this->money += amount;
    cash.setString(std::to_string(money));
}

int Game::getRoundNumber()
{
    return this->round_number;
}

void Game::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    rt.draw(*map);
    for(auto &enemy : enemyList)
        if(enemy != nullptr)
            rt.draw(*enemy);
    for(auto tower : towerList)
        rt.draw(*tower);
    rt.draw(score);
    rt.draw(cash);
    rt.draw(round);
    rt.draw(health_indicator);
    if(gameOver){
        if(playerWon)
            rt.draw(player_won);
        else
            rt.draw(game_over);

    }
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

void Game::loadRoundsFromFile(){
    std::ifstream r_file;
    r_file.open("../maps/rounds.txt");//tiedoston voi toki laittaa muuallekin kuin "maps" -kansioon, kunhan polkua muutetaan
    std::string round;
    rounds.erase(rounds.begin(), rounds.end());

    while(!((r_file.eof()) or (r_file.fail()))) {
        std::getline(r_file, round);
        rounds.push_back(round);
    }
    r_file.close();
    set_rounds(rounds);
}
    
void Game::sellTower(sf::Vector2f position){
    float factor = 0.75;
    Tower* tower = getTower(position);
    money += tower->get_cost() * factor;
    cash.setString(std::to_string(money));
    removeTower(position);
}

std::vector<std::pair<std::string, std::string>>& Game::getObjectsToSave()
{
    std::pair<std::string, std::string> newPair;

    newPair = {"map", map->getMapName() + ";"};
    objectsToSave.push_back(newPair);

    newPair = {"health", std::to_string(getHealth()) + ";"};
    objectsToSave.push_back(newPair);

    newPair = {"round", std::to_string(getRoundNumber()) + ";"};
    objectsToSave.push_back(newPair);

    newPair = {"money", std::to_string(getMoney())  + ";"};
    objectsToSave.push_back(newPair);

    newPair = {"score", std::to_string(getScore())  + ";"};
    objectsToSave.push_back(newPair);    

    for (auto tower : towerList)
    {
        std::string second = std::to_string(tower->get_type()) + ";" +
                             std::to_string(tower->getPos().x) + ";" + 
                             std::to_string(tower->getPos().y) + ";";

        newPair = {"tower", second};
        objectsToSave.push_back(newPair);
    }

    return objectsToSave;
}

std::vector<std::pair<std::string, std::string>>& Game::getObjectsToLoad()
{
    return objectsToLoad;
}

void Game::loadObjects()
{
    save::Load load(getObjectsToLoad());
    if(load.gameSaveExists()){

        reset();

        for (auto object : objectsToLoad)
        {
            std::string str = object.first;

            if (str == "money")
            {
                this->money = std::stoi(object.second);
            }
            else if (str == "health")
            {
                this->health = std::stoi(object.second);
            }
            else if (str == "score")
            {
                this->points = std::stoi(object.second);
            }
            else if (str == "map")
            {
                object.second.pop_back();
                this->setNextMap(object.second);
            }
            else if (str == "round")
            {
                this->round_number = std::stoi(object.second);
                rounds.erase(rounds.begin(), rounds.begin()+round_number-1);
                set_rounds(rounds);
            }
            else if (str == "tower")
            {
                sf::Vector2f pos{0,0};
                Tower* newtower;

                switch (std::stoi(parseObjectMembers(object, 1)))
                {
                    case 11:
                        //std::cout << "Basic" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new BasicTower;
                        break;
                    case 12:
                        //std::cout << "Freeze" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new FreezeTower;
                        break;
                    case 21:
                        //std::cout << "Blast" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new BlastTower;
                        break;
                    case 22:
                        //std::cout << "MultiFreeze" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new MultiFreezeTower;
                        break;
                    case 23:
                        //std::cout << "Precision" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new PrecisionTower;
                        break;
                    /* UNFINISHED STUFF BELOW
                    case 31:
                        std::cout << "Obliterator" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new Obliterator;
                        break;
                    case 32:
                        std::cout << "FreezeWave" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new FreezeWaveTower;
                        break;
                    case 33:
                        std::cout << "DeathRay" << std::endl;
                        pos.x = std::stof(parseObjectMembers(object, 2));
                        pos.y = std::stof(parseObjectMembers(object, 3));
                        newtower = new DeathRay;
                        break;
                    */
                    default:
                        std::cout << "Tower type doesn't exist" << std::endl;
                        break;
                    
                }

                if (pos.x)
                {
                    //std::cout << "Created saved tower\n";
                    newtower->setPosition(pos);
                    newtower->toggleRange();
                    towerList.push_back(newtower);
                    map->addTower(pos);
                }
            }
            else
            {

            }
        }
    }
    score.setString(std::to_string(points));
    cash.setString(std::to_string(money));
    round.setString("Round " + std::to_string(round_number));
    health_indicator.setString(std::to_string(health));
}

std::string Game::parseObjectMembers(std::pair<std::string, std::string> &object, int memberIndex)
{
    std::string member;
    std::string line = object.second;
    int counter = 0;

    for (auto i = 0; i < line.length(); i++)
    {
        if (line.substr(i, 1) == ";")
        {
            counter++;

            if (counter == memberIndex)
            {
                return member;
            }

            member = "";
        }
        else
        {
            member += line.substr(i, 1);
        }

    }

    return "";
}


void Game::upgradeTower(Tower* tower) {
    if(tower == nullptr) {
        std::cout << "NULL" << std::endl;
        return;
    }
    sf::Vector2f pos = tower->getPos();
    int t_type = tower->get_type();
    if(t_type < 20) {//tier 1
        if(t_type == 11) {//basic, upgrade only to blast for now, need to add more buttons later
            Tower* newtower = new BlastTower();
            int cost = newtower->get_cost();
            if((cost / 2) <= money) {
                removeTower(pos);
                money -= cost / 2;
                cash.setString(std::to_string(money));
                std::cout << "upgraded FreezeTower to MultiFreezeTower for " << cost << std::endl;
                newtower->setPosition(pos);
                newtower->toggleRange();
                towerList.push_back(newtower);
                map->addTower(pos);
            }
            else {
                delete newtower;
                std::cout << "not enough money" << std::endl;
            }
            return;
        }
        else if(t_type == 12) {//(simple) freeze, upgrade to multifreeze
            Tower* newtower = new MultiFreezeTower();
            int cost = newtower->get_cost();
            if((cost / 2) <= money) {
                removeTower(pos);
                money -= cost / 2;
                cash.setString(std::to_string(money));
                std::cout << "upgraded FreezeTower to MultiFreezeTower for " << cost << std::endl;
                newtower->setPosition(pos);
                newtower->toggleRange();
                towerList.push_back(newtower);
                map->addTower(pos);
            }
            else {
                delete newtower;
                std::cout << "not enough money" << std::endl;
            }
            return;
        }
    }
/*
    else if(t_type < 30) {//tier 2
        if(t_type == 21) {//blast, upgrade to super-(what else?:P)-blast once finished
            
        }
        else if(t_type == 22) {//multifreeze, upgrade to freeze pulse once finished
            
        }
        else if(t_type == 23) {//precision, upgrade to death ray/whatever
            
        }
    }
*/
    else {
        std::cout << "upgrade not available to #" << tower->get_type() << std::endl;
    }
    return;
}

bool Game::getIsGameOver()
{
    return gameOver;
}

int Game::getScore(){
    return points;
}

void Game::reset(){
    for(auto& tower : towerList){
        map->removeTower(tower->getPos());
        delete tower;
        tower = nullptr;
    }
    towerList.erase(remove(towerList.begin(), towerList.end(), nullptr), towerList.end());

    for(auto& enemy : enemyList){
        enemy.reset();
    }
    enemyList.erase(remove(enemyList.begin(), enemyList.end(), nullptr), enemyList.end());
    gameOver = false;
    playerWon = false;
    health = 100;
    money = 6500;
    round_number = 1;
    isBuildPhase = true;
    isGamePaused = false;
    enemyPause = 0;
    towerPause = 0;
    points = 0;
    loadRoundsFromFile();
    score.setString(std::to_string(points));
    cash.setString(std::to_string(money));
    round.setString("Round " + std::to_string(round_number));
    health_indicator.setString(std::to_string(health));
}

void Game::setNumerOfMaps(){
    int counter = 0;
    std::string line;
    std::ifstream maps;
    maps.open("../maps/maps.txt");
    if(maps.is_open())
        while(std::getline(maps, line))
            counter++;
    numberOfMaps = counter;
}

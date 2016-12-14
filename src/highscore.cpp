#include "highscore.hpp"
#include <sstream>
#include <iostream>

HighScore::HighScore(sf::Font* font, Game* game) :
    font(font),
    game(game),
    filepath("../scores.txt")
{
    readScores();
    addText.setFont(*font);
    addText.setCharacterSize(32);
    addText.setStyle(sf::Text::Bold);
    addText.setString("Please enter your initials");
    addText.setPosition(box_position + sf::Vector2f(-112, -48));
}

void HighScore::getUsername(sf::Event event){
    if(adding && event.type == sf::Event::TextEntered){
        if (event.text.unicode < 123 && event.text.unicode > 96){
            char letter = static_cast<char>(event.text.unicode - 32);
            if(username.size() < 3)
                username.push_back(letter);
        }
    }
    if(adding && event.type == sf::Event::KeyPressed){
        if(username.size() == 3 && event.key.code == sf::Keyboard::Return){
            adding = false;
            show = true;
            addScore();
        }
        if(event.key.code == sf::Keyboard::BackSpace){
            username.pop_back();
        }
    }
}
    

void HighScore::addScore(){
    int points = game->getScore();
    std::pair<std::string, int> score (username, points);
    scores.push_back(score);
    std::sort(scores.begin(), scores.end(),
            [](std::pair<std::string,int> &A, std::pair<std::string,int> &B) -> bool
            { return A.second > B.second; });
    writeScores();
}

void HighScore::showScores(){
    show = true;
}
void HighScore::hideScores(){
    show = false;
}
bool HighScore::isShowing(){
    return show;
}

void HighScore::readScores(){
    std::ifstream scoreFile;
    std::string line, tmp;
    std::pair<std::string, int> score;
    scoreFile.open(filepath);
    if(scoreFile.is_open()){
        while (std::getline(scoreFile, line)){
            std::stringstream linestream(line);
            std::getline(linestream, score.first, ';');
            std::getline(linestream, tmp, ';');
            score.second = std::stoi(tmp);
            scores.push_back(score);
        }
        scoreFile.close();
    }
}

void HighScore::writeScores(){
    std::ofstream scoreFile;
    scoreFile.open(filepath);
    if(scoreFile.is_open()){
        for(auto score : scores)
            scoreFile << score.first << ";" << score.second << std::endl;
        scoreFile.close();
    }
}

std::vector<sf::Text> HighScore::getScores() const{
    std::vector<sf::Text> drawable_scores;
    int i = 0;
    for(auto score : scores){
        std::string score_as_string = std::to_string(i+1) + ". " + score.first
            + " " + std::to_string(score.second);
        sf::Text text;
        text.setFont(*font);
        text.setCharacterSize(32);
        text.setStyle(sf::Text::Bold);
        text.setString(score_as_string);
        text.setPosition(first_position.x, i * delta_score2score.y + first_position.y);
        drawable_scores.push_back(text);
        if(++i >= 10)
            break;
    }
    return drawable_scores;
}

std::vector<std::pair<gui::Menu,gui::Text> > HighScore::getBoxes() const{
    std::vector<std::pair<gui::Menu,gui::Text> > boxes;
    for(int i=0; i<3; i++){
        std::pair<gui::Menu, gui::Text> box;
        std::string letter = "";
        box.first = gui::Menu(box_size, sf::Vector2f(box_position.x + i*delta_box.x, box_position.y), sf::Color::White);
        if(username.size() > i)
            letter = username.substr(i,1);
        box.second = gui::Text(letter, *font, &box.first);
        box.second.setColor(sf::Color::Black);
        boxes.push_back(box);
    }
    return boxes;
}

void HighScore::setAddingTrue(){
    adding = true;
}
        
void HighScore::draw(sf::RenderTarget& rt, sf::RenderStates states) const{
    if(adding && game->getIsGameOver()){
        for(auto box : getBoxes()){
            rt.draw(addText);
            rt.draw(box.first);
            rt.draw(box.second);
        }
    }
    else if(show)
        for(auto score : getScores())
            rt.draw(score);
}

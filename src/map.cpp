/*
* (map.cpp)
* Author: Caleb Jhones
*/

#include "map.h"

// the parameterized constructor
Map::Map(string path){
    myBackground = path;
}

// here be getters and setters
int Map::getScore(){
    return myScore;
}

void Map::setScore(int s){
    myScore = s;
}

void Map::setImage(string s){
    myBackground = s;
}

// draws the background and the current score
void Map::draw(RenderTarget& window){
    // the background for the game is actually just a sprite that fills the whole screen
    Texture t;
    t.loadFromFile(myBackground);
    Sprite s;
    s.setTexture(t);
    s.setPosition(0, 0);
    window.draw(s);

    // write points to the screen too
    // Draw them after the background so they're on top!
    Font f;
    f.loadFromFile("../data/LiberationMono-Regular.ttf");
    Text text;
    text.setFont(f);
    text.setString("Score: " + to_string(myScore));
    text.setPosition(10, 455);
    text.setColor(Color::Green);
    text.setScale(1, 1);
    window.draw(text);

}

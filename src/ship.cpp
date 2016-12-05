/*
* (ship.cpp)
* Author: Caleb Jhones
*/

#include "ship.h"

// parameterized constructor
// x and y are coordinates for the sprite, path is the filepath to the sprite image
Ship::Ship(int x, int y, string path){
    myX = x;
    myY = y;
    myTexture = path;
}

// getters and setters
int Ship::getXPos(){
    return myX;
}

int Ship::getYPos(){
    return myY;
}

void Ship::setXPos(int x){
    myX = x;
}

void Ship::setYPos(int y){
    myY = y;
}

void Ship::setSpriteTexture(string path){
    myTexture = path;
}

// draws the ship to the RenderTarget
void Ship::draw(RenderTarget& window){
    Texture t;
    t.loadFromFile(myTexture);
    Sprite s;
    s.setTexture(t);
    s.setPosition((float) myX, (float) myY);
    // scaled down by a factor of 20%, so the ship isn't huge
    s.setScale((float) 1.0/5, (float) 1.0/5);
    window.draw(s);
}

// mives the ship based on the integer that is passed from whatever called it
void Ship::move(int dir){
    // moves left after checking if it is too close to the left side of the window
    if (dir == 0 && myX > 5)
        myX -= 10;
    // moves right after checking if it is too close to the right side of the window
    else if (dir == 1 && myX < 982)
        myX += 10;
    else
        return;
}

// fires at the enemies (cause that's the point of the game!)
void Ship::fire(vector<Enemy>& enemies, Map& map, RenderTarget& window){
    // the "projectile" is actually a laser beam :P
    // this beam is just a simple line that is drawn to the screen from the middle of the ship's sprite
    RectangleShape line;
    line.setFillColor(Color::Red);
    // loops thru the vector of enemies and checks if there are any that are hit
    // the criteria for being hit is the x value of the ship being somewhere within the width of the enemy's sprite
    for(int i = 0; i < enemies.size(); i++){
        // this if registers a hit, draws the appropriate line, and removes the destroyed enemy from the vector
        if(abs(myX - enemies.at(i).getXPos()) < 15){
            // this line goes from the ship to the enemy, not the edge of the screen
            line.setSize(Vector2f(2, (float)(enemies.at(i).getYPos() - myY + 15)));
            line.setPosition(myX + 19, myY);
            window.draw(line);
            // also, we want to update the score that's drawn on the map based on the hits
            map.setScore(map.getScore() + enemies.at(i).getPointVal());
            enemies.erase(enemies.begin() + i);
            // no need to keep looping, so return to the callee
            return;
        }
        // this else just means the enemy at index i wasn't hit;
        // it says nothing of the rest of the enemies in the vector
        else
            continue;
    }
    // if we went all the way thru the vector with no hits, it was a miss
    // draw a line from the ship to the top edge of the screen, and then return
    line.setSize(Vector2f(2, myY));
    line.setPosition(myX + 19, 0);
    window.draw(line);
    return;
}


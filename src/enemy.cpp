/*
* (enemy.cpp)
* Author: Caleb Jhones
*/

#include "enemy.h"

// default constructor, so we can make empty arrays of type enemy
Enemy::Enemy(){
    myX = 0;
    myY = 0;
    myPointVal = 1;
    myTexture = "";
}

// parameterized constructor. x and y are the starting positions,
// points is the point value for destroying the enemy, and path
// is the filepath to the sprite's texture
Enemy::Enemy(int x, int y, int points, string path){
    setXPos(x);
    setYPos(y);
    setPointVal(points);
    myTexture = path;
}

// getters and setters
int Enemy::getXPos(){
    return myX;
}

int Enemy::getYPos(){
    return myY;
}

int Enemy::getPointVal(){
    return myPointVal;
}

void Enemy::setXPos(int x){
    if(x > 0 && x < 994) // guarantees the enemy doesn't draw off of the screen
        myX = x;
    else
        myX = 0;
}

void Enemy::setYPos(int y){
    if(y > 0 && y < 743) // guarantees the enemy doesn't draw off of the screen
        myY = y;
    else
        myY = 0;
}

void Enemy::setPointVal(int points){
    // checks if 'points' is positive
    if(points > 0)
        myPointVal = points;
    // if it isn't, the value 5 is assigned
    else
        myPointVal = 5;
}

void Enemy::setTexture(string path){
    myTexture = path;
}

// causes an enemy to fire at the player
// takes the player's x coordinate, so we can compare it to the enemy's
// returns a bool of whether the player is hit or not (true = hit; false = miss)
bool Enemy::fire(int x, RenderTarget& window){
    RectangleShape line;
    line.setFillColor(Color::Cyan);
    // checks if the x coordinates of the enemy and the ship are the same
    // if so, it registers as a hit. a line is drawn and 'true' is returned
    if(abs(myX - x) <= 19){
        line.setSize(Vector2f(2, 768 - myY));
        line.setPosition(myX + 25, myY + 70);
        window.draw(line);
        return true;
    }
    // if they aren't the same, it is a miss. the line is still drawn,
    // but false is returned
    else {
        line.setSize(Vector2f(2, 768 - myY));
        line.setPosition(myX + 25, myY + 70);
        window.draw(line);
        return false;
    }
}

// draw an enemy to the render target, passed by reference
// scaled down to 30% of the size of the original image
void Enemy::draw(RenderTarget& window){
    Texture t;
    t.loadFromFile(myTexture);
    Sprite s;
    s.setTexture(t);
    s.setPosition((float) myX, (float) myY);
    s.setScale((float) 3.0/10, (float) 3.0/10);
    window.draw(s);
}


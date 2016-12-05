/*
* (enemy.h)
* Author: Caleb Jhones
*/

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Enemy{
    public:
        Enemy();
        Enemy(int, int, int, string); // 2 ints are x & y positions, the third is a point value, str is path to texture pic
        int getXPos(); // standard getters and setters, but only the ones that are necessary
        int getYPos();
        int getPointVal();
        void setXPos(int);
        void setYPos(int);
        void setPointVal(int);
        void setTexture(string);
        bool fire(int x, RenderTarget& window); // int is player's x value, RenderTarget is the render window
        void draw(RenderTarget& window);

    private:
        int myX; // x position in the window
        int myY; // y position in the window
        int myPointVal; // the point value associated with this specific enemy
        std::string myTexture; // filepath to texture file for sprite
};


/*
* (ship.h)
* Author: Caleb Jhones
*/

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "enemy.h"
#include "map.h"

using namespace std;
using namespace sf;

class Ship{
    public:
        Ship(int, int, string); // ints are x & y positions, str is pat to texture pic
        int getXPos(); // standard getters and setters, probably won't use any of the ones for Y
        int getYPos();
        void setXPos(int);
        void setYPos(int);
        void setSpriteTexture(string);
        void draw(RenderTarget& window);
        void move(int); // moves the ship
        // fires the ship's weapon, and updates the score counter based on any hits
        // takes the vector of enemies so it can check for hits
        // takes the map so it can update the score
        // takes a RenderTarget so it can draw the laser beam
        void fire(vector<Enemy>& enemies, Map& map, RenderTarget& window);

    private:
        int myX; // x position in the window
        int myY; // y position in the window, probably won't change once its set at the beginning
        string myTexture; // filepath to texture file for sprite
};


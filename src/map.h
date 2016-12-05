/*
* (map.h)
* Author: Caleb Jhones
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Map{
    public:
        Map(string); // the ints are the anchors for the background image, str is path to img
        int getScore(); // standard getters and setters
        void setScore(int);
        void setImage(string);
        void draw(RenderTarget& window);

    private:
        int myScore; // score counter
        string myBackground; // filepath to background picture

};

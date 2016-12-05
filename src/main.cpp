/* CSCI 261 Final Project: Space Battle
* (main.cpp)
* Author: Caleb Jhones
*
* Description: This is a game that is very similar to Galaga or Space Invaders.
*/

#include "enemy.h"
#include "map.h"
#include "ship.h"

#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
using namespace sf;

// width and height of the background, which dictates the size of the window
const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 500;
// easily change the number of enemies drawn to the screen
// more than 16 requires a second row, which is not currently supported
const int NUM_ENEMIES = 15;

int main(){

    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Battle!", Style::Titlebar | Style::Close);
    // read font from file
    Font font;
    font.loadFromFile("../data/LiberationMono-Regular.ttf");
    // initialize map, player ship, and enemies
    Ship player(WIDTH/2, HEIGHT-100, "../data/player.png");
    Map map("../data/star_background.jpg");
    // loops thru the vector of enemies and fills each spot with a specific enemy
    vector<Enemy> enemies;
    for(int i = 0; i < NUM_ENEMIES; i++){
        Enemy e;
        e.setXPos(40 + 60 * i);
        e.setYPos(50);
        if(i % 3 == 0) {
            e.setTexture("../data/enemy1.png");
            e.setPointVal(5);
        }
        else if(i % 3 == 1) {
            e.setTexture("../data/enemy2.png");
            e.setPointVal(10);
        }
        else{
            e.setTexture("../data/enemy3.png");
            e.setPointVal(15);
        }
        enemies.push_back(e);
    }

    // seed the pRNG, which will decide which enemy gets to fire
    srand(time(NULL));
    int toFire; // a variable that holds which enemy gets to fire
    int count = 0; // for controlling when the enemy fires
    bool dead = false; // for knowing if you're dead
    bool playerFired = false; // to control player's firing
    map.setScore(0); // set initial score to 0

    while(window.isOpen()){

        count++; // decides when the enemies fire

        // check win/lose conditions, responding accordingly
        if(dead){
            // end game with losing screen
            RectangleShape rect(Vector2f(350,100));
            rect.setFillColor(Color(100, 100, 100));
            rect.setPosition(WIDTH/2 - 175, HEIGHT/2 - 50);
            window.draw(rect);
            // Text to display the game-over message
            Text t;
            t.setFont(font);
            t.setString("GAME OVER");
            t.setPosition(WIDTH/2 - 160, HEIGHT/2 - 50);
            t.setColor(Color::Red);
            t.setScale(2.0, 2.0);
            window.draw(t);
            // need this here also, because the one below doesn't get called before the break is executed
            window.display();
            // waits for 3s before closing the program
            sleep(milliseconds(3000));
            break;

        } if (enemies.empty()){
            // end game with winning screen
            RectangleShape rect(Vector2f(350,100));
            rect.setFillColor(Color(100, 100, 100));
            rect.setPosition(WIDTH/2 - 175, HEIGHT/2 - 50);
            window.draw(rect);
            // Text to display the winning message
            Text t;
            t.setFont(font);
            t.setString("YOU WIN");
            t.setPosition(WIDTH/2 - 130, HEIGHT/2 - 50);
            t.setColor(Color::Blue);
            t.setScale(2.0, 2.0);
            window.draw(t);
            // same as above
            window.display();
            sleep(milliseconds(3000));
            break;

        } else {
            // draw the map
            map.draw(window);
            // move player
            player.draw(window);
            // allow player to fire
            if(playerFired)
                player.fire(enemies, map, window);
            // draw enemies (important that this is after the player fires, so it removes enemies accordingly
            for(int i = 0; i < enemies.size(); i++)
                enemies.at(i).draw(window);
            // allows a random enemy to fire at a random interval, based on how many times the while loop has run
            if(count * (rand() % 11) % 53 == 0){ // this just gives a random but fairly even amount of fire from the enemies
                toFire = rand() % enemies.size();
                dead = enemies.at(toFire).fire(player.getXPos(), window);
                // this sets a bool that, on the next loop, allows the program to check if there was a hit on the player's ship
                // the enemy that fires is randomly selected from the enemies still in the array
            }
        }
        //reset the firing bool
        playerFired = false;
        //update what is being displayed
        window.display();

        // an event used to either close the window, move the player's sprite, or allow the player to fire
        Event e;
        while(window.pollEvent(e)){
            // if the close button is pressed, close the window
            if(e.type == Event::Closed)
                window.close();
            // if a keyboard key is pressed, do something appropriate
            else if(e.type == Event::KeyPressed){
                switch(e.key.code){
                    case Keyboard::Left:
                        player.move(0); // passing 0 moves left
                        break;
                    case Keyboard::Right:
                        player.move(1); // passing 1 moves right
                        break;
                    case Keyboard::Up:
                        playerFired = true; // this sets the playerFired variable, which is used to draw laser beams and check for hits
                        break;
                    case Keyboard::Escape:
                        window.close(); // an easy way to exit the program without the mouse
                        break;
                }
            }
        }
    }

    return 0;
}


/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30, 2020
Description:
Class Maze, which draws the maze walls, coins, and power ups.
*/

#include "Maze.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h> // Include the GLUT header file

using namespace std;

//Default constructor
Maze::Maze()
{
    //Initialize Coin Location
    ifstream file("Initial_Coin_Location.csv");
    for (int row = 0; row < 22; ++row) //loop through each line
    {
        string line;
        getline(file, line);
        if (!file.good())
        {
            break;
        }
        stringstream iss(line);
        for (int col = 0; col < 19; ++col) //loop through each value
        {
            std::string val;
            std::getline(iss, val, ',');
            if (!iss.good())
            {
                break;
            }
            std::stringstream convertor(val);
            convertor >> coinLocation[row][col]; //store in array
        }
    }
    ifstream close();

    //initialize powerups
    for (int ndx = 0; ndx < 4; ndx++)
    {
        powerupAvailable[ndx] = 1;
    }
    
    powerupMode = 0;//start game NOT in powerup mode
    coinCount = 0; //count how many coins pacman has eaten
    lifeCount = 3; //start with 3 lives
}

//----------------------------------------------------------------------
    //Function: drawMaze()
    //Input: none
    //Output: none
    // Description:
    // Draws the initial board setup, with maze, coins, and power ups
    //----------------------------------------------------------------------
void Maze::drawMaze()
{
    //Outer boarder
    drawWall(18.0f, 0.0f, 0.0f, 0.0f, 1.0f); //front
    drawWall(18.0f, 0.0f, 21.0f, 0.0f, 1.0f); //back
    drawWall(8.0f, 0.0f, 0.0f, -1.0f, 0.0f); //left side, from front to back
    drawWall(3.0f, 0.0f, 8.0f, 0.0f, 1.0f);
    drawWall(2.0f, 3.0f, 8.0f, -1.0f, 0.0f);
    drawWall(3.0f, 0.0f, 10.0f, 0.0f, 1.0f);
    drawWall(3.0f, 0.0f, 12.0f, 0.0f, 1.0f);
    drawWall(2.0f, 3.0f, 12.0f, -1.0f, 0.0f);
    drawWall(3.0f, 0.0f, 14.0f, 0.0f, 1.0f);
    drawWall(7.0f, 0.0f, 14.0f, -1.0f, 0.0f);
    drawWall(8.0f, 18.0f, 0.0f, -1.0f, 0.0f); //right side, from front to back
    drawWall(3.0f, 15.0f, 8.0f, 0.0f, 1.0f);
    drawWall(2.0f, 15.0f, 8.0f, -1.0f, 0.0f);
    drawWall(3.0f, 15.0f, 10.0f, 0.0f, 1.0f);
    drawWall(3.0f, 15.0f, 12.0f, 0.0f, 1.0f);
    drawWall(2.0f, 15.0f, 12.0f, -1.0f, 0.0f);
    drawWall(3.0f, 15.0f, 14.0f, 0.0f, 1.0f);
    drawWall(7.0f, 18.0f, 14.0f, -1.0f, 0.0f);
    // Internal Walls from front to back, then left to right
    //1/5 Section Walls
    drawWall(1.0f, 0.0f, 4.0f, 0.0f, 1.0f); //bottom left -
    drawWall(5.0f, 2.0f, 2.0f, 0.0f, 1.0f);//bottom left T
    drawWall(2.0f, 5.0f, 2.0f, -1.0f, 0.0f);
    drawWall(5.0f, 11.0f, 2.0f, 0.0f, 1.0f); //bottom right T
    drawWall(2.0f, 13.0f, 2.0f, -1.0f, 0.0f);
    drawWall(4.0f, 7.0f, 4.0f, 0.0f, 1.0f); //bottom middle T
    drawWall(2.0f, 9.0f, 2.0f, -1.0f, 0.0f);
    drawWall(1.0f, 17.0f, 4.0f, 0.0f, 1.0f);
    // 2/5 Section Walls
    drawWall(1.0f, 2.0f, 6.0f, 0.0f, 1.0f); //bottom left 7
    drawWall(2.0f, 3.0f, 4.0f, -1.0f, 0.0f);
    drawWall(2.0f, 5.0f, 6.0f, 0.0f, 1.0f); //bottom left --
    drawWall(4.0f, 7.0f, 8.0f, 0.0f, 1.0f); //middle T
    drawWall(2.0f, 9.0f, 6.0f, -1.0f, 0.0f);
    drawWall(1.0f, 15.0f, 6.0f, 0.0f, 1.0f); //bottom right 7
    drawWall(2.0f, 15.0f, 4.0f, -1.0f, 0.0f);
    drawWall(2.0f, 11.0f, 6.0f, 0.0f, 1.0f); //bottom right --
    // 3/5 Section Walls
    drawWall(2.0f, 5.0f, 8.0f, -1.0f, 0.0f); //left |
    drawWall(2.0f, 13.0f, 8.0f, -1.0f, 0.0f); //left |
    drawWall(4.0f, 7.0f, 10.0f, 0.0f, 1.0f); //ghost box
    drawWall(4.0f, 7.0f, 12.0f, 0.0f, 1.0f); 
    drawWall(2.0f, 7.0f, 10.0f, -1.0f, 0.0f); 
    drawWall(2.0f, 11.0f, 10.0f, -1.0f, 0.0f);
    // 4/5 Section Walls
    drawWall(2.0f, 5.0f, 14.0f, 0.0f, 1.0f); //Top left T
    drawWall(4.0f, 5.0f, 12.0f, -1.0f, 0.0f);
    drawWall(4.0f, 7.0f, 16.0f, 0.0f, 1.0f); //Top middle T
    drawWall(2.0f, 9.0f, 14.0f, -1.0f, 0.0f);
    drawWall(2.0f, 11.0f, 14.0f, 0.0f, 1.0f); //Top right T
    drawWall(4.0f, 13.0f, 12.0f, -1.0f, 0.0f);
    drawWall(1.0f, 2.0f, 16.0f, 0.0f, 1.0f); //Top left -
    drawWall(1.0f, 15.0f, 16.0f, 0.0f, 1.0f); //Top right -
    //5/5 Section Walls
    drawWall(1.0f, 2.0f, 18.0f, 0.0f, 1.0f); //Top Left square box
    drawWall(1.0f, 2.0f, 19.0f, 0.0f, 1.0f);
    drawWall(1.0f, 2.0f, 18.0f, -1.0f, 0.0f);
    drawWall(1.0f, 3.0f, 18.0f, -1.0f, 0.0f);
    drawWall(2.0f, 5.0f, 18.0f, 0.0f, 1.0f); //Top Left rectangle box
    drawWall(2.0f, 5.0f, 19.0f, 0.0f, 1.0f);
    drawWall(1.0f, 5.0f, 18.0f, -1.0f, 0.0f);
    drawWall(1.0f, 7.0f, 18.0f, -1.0f, 0.0f);
    drawWall(3.0f, 9.0f, 18.0f, -1.0f, 0.0f); //Top middle |
    drawWall(1.0f, 15.0f, 18.0f, 0.0f, 1.0f); //Top right square box
    drawWall(1.0f, 15.0f, 19.0f, 0.0f, 1.0f);
    drawWall(1.0f, 15.0f, 18.0f, -1.0f, 0.0f);
    drawWall(1.0f, 16.0f, 18.0f, -1.0f, 0.0f);
    drawWall(2.0f, 11.0f, 18.0f, 0.0f, 1.0f); //Top right rectangle box
    drawWall(2.0f, 11.0f, 19.0f, 0.0f, 1.0f);
    drawWall(1.0f, 11.0f, 18.0f, -1.0f, 0.0f);
    drawWall(1.0f, 13.0f, 18.0f, -1.0f, 0.0f);

    //round edges for maze, from front to back, left to right
    drawVertex(0.0f, 0.0f);
    drawVertex(18.0f, 0.0f);
    drawVertex(2.0f, 2.0f);
    drawVertex(7.0f, 2.0f);
    drawVertex(9.0f, 2.0f);
    drawVertex(11.0f, 2.0f);
    drawVertex(16.0f, 2.0f);
    drawVertex(0.0f, 4.0f);
    drawVertex(1.0f, 4.0f);
    drawVertex(3.0f, 4.0f);
    drawVertex(5.0f, 4.0f);
    drawVertex(7.0f, 4.0f);
    drawVertex(9.0f, 4.0f);
    drawVertex(11.0f, 4.0f);
    drawVertex(13.0f, 4.0f);
    drawVertex(15.0f, 4.0f);
    drawVertex(17.0f, 4.0f);
    drawVertex(18.0f, 4.0f);
    drawVertex(2.0f, 6.0f);
    drawVertex(3.0f, 6.0f);
    drawVertex(5.0f, 6.0f);
    drawVertex(7.0f, 6.0f);
    drawVertex(9.0f, 6.0f);
    drawVertex(11.0f, 6.0f);
    drawVertex(13.0f, 6.0f);
    drawVertex(15.0f, 6.0f);
    drawVertex(16.0f, 6.0f);
    drawVertex(0.0f, 8.0f);
    drawVertex(3.0f, 8.0f);
    drawVertex(5.0f, 8.0f);
    drawVertex(7.0f, 8.0f);
    drawVertex(9.0f, 8.0f);
    drawVertex(11.0f, 8.0f);
    drawVertex(13.0f, 8.0f);
    drawVertex(15.0f, 8.0f);
    drawVertex(18.0f, 8.0f);
    drawVertex(0.0f, 10.0f);
    drawVertex(3.0f, 10.0f);
    drawVertex(5.0f, 10.0f);
    drawVertex(7.0f, 10.0f);
    drawVertex(11.0f, 10.0f);
    drawVertex(13.0f, 10.0f);
    drawVertex(15.0f, 10.0f);
    drawVertex(18.0f, 10.0f);
    drawVertex(0.0f, 12.0f);
    drawVertex(3.0f, 12.0f);
    drawVertex(5.0f, 12.0f);
    drawVertex(7.0f, 12.0f);
    drawVertex(11.0f, 12.0f);
    drawVertex(13.0f, 12.0f);
    drawVertex(15.0f, 12.0f);
    drawVertex(18.0f, 12.0f);
    drawVertex(0.0f, 14.0f);
    drawVertex(3.0f, 14.0f);
    drawVertex(5.0f, 14.0f);
    drawVertex(7.0f, 14.0f);
    drawVertex(9.0f, 14.0f);
    drawVertex(11.0f, 14.0f);
    drawVertex(13.0f, 14.0f);
    drawVertex(15.0f, 14.0f);
    drawVertex(18.0f, 14.0f);
    drawVertex(2.0f, 16.0f);
    drawVertex(3.0f, 16.0f);
    drawVertex(5.0f, 16.0f);
    drawVertex(7.0f, 16.0f);
    drawVertex(9.0f, 16.0f);
    drawVertex(11.0f, 16.0f);
    drawVertex(13.0f, 16.0f);
    drawVertex(15.0f, 16.0f);
    drawVertex(16.0f, 16.0f);
    drawVertex(2.0f, 18.0f);
    drawVertex(3.0f, 18.0f);
    drawVertex(5.0f, 18.0f);
    drawVertex(7.0f, 18.0f);
    drawVertex(9.0f, 18.0f);
    drawVertex(11.0f, 18.0f);
    drawVertex(13.0f, 18.0f);
    drawVertex(15.0f, 18.0f);
    drawVertex(16.0f, 18.0f);
    drawVertex(2.0f, 19.0f);
    drawVertex(3.0f, 19.0f);
    drawVertex(5.0f, 19.0f);
    drawVertex(7.0f, 19.0f);
    drawVertex(11.0f, 19.0f);
    drawVertex(13.0f, 19.0f);
    drawVertex(15.0f, 19.0f);
    drawVertex(16.0f, 19.0f);
    drawVertex(0.0f, 21.0f);
    drawVertex(9.0f, 21.0f);
    drawVertex(18.0f, 21.0f);

    //place coins and power ups on maze
    drawAllCoins();
    
}

//----------------------------------------------------------------------
    //Function: drawWall()
    //Input: (float length, float transX, float transY, float rotateX, float rotateY)
    //Output: none
    // Description:
    // Draws a single cylindrical blue wall for the maze, at the specified location
    //----------------------------------------------------------------------
void Maze::drawWall(float length, float transX, float transY, float rotateX, float rotateY)
{
    glPushMatrix();
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(transX, transY, 0);
    glRotatef(90.0f, rotateX, rotateY, 0.0f);
    glColor3f(0.0f, 0.5f, 1.0f); // set drawing color blue
    gluCylinder(quadratic, 0.1f, 0.1f, length, 32, 32);
    glPopMatrix();
}

//----------------------------------------------------------------------
    //Function: drawVertex()
    //Input: float transX, float transY
    //Output: none
    // Description:
    // Draws a single small blue sphere to make the maze vertices smooth, at the specified location
    //----------------------------------------------------------------------
void Maze::drawVertex(float transX, float transY)
{
    glColor3f(0.0f, 0.5f, 1.0f); // set drawing color blue
    glPushMatrix();
    glTranslatef(transX, transY, 0.0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

//----------------------------------------------------------------------
    //Function: drawCoin()
    //Input: float transX, float transY
    //Output: none
    // Description:
    // Draws a single spherical silver coin, at the specified location
    //----------------------------------------------------------------------
void Maze::drawCoin(float transX, float transY)
{
    glColor3f(0.9, 0.9, 0.9); // set drawing color silver
    glPushMatrix();
    glTranslatef(transX, transY, 0.0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

    //----------------------------------------------------------------------
    //Function: drawAllCoins()
    //Input: none
    //Output: none
    // Description:
    // Draws all of the coins, lives, and power ups based off of locations in array coinLocation
    //----------------------------------------------------------------------
void Maze::drawAllCoins()
{
    //Draw coins
    for (int row = 0; row < 22; ++row)
    {
        for (int col = 0; col < 19; ++col)
        {
            if (coinLocation[row][col] == 1) //if the array indicates a coin is present
            {
                drawCoin(col, row);
            }
        }
    }

    //Draw power ups
    if (powerupAvailable[0]) 
    {
        drawPowerUp(1.0f, 5.0f);
    }
    if (powerupAvailable[1])
    {
        drawPowerUp(17.0f, 5.0f);
    }
    if (powerupAvailable[2])
    {
        drawPowerUp(1.0f, 19.0f);
    }
    if (powerupAvailable[3])
    {
        drawPowerUp(17.0f, 19.0f);
    }

    //draw lives
    if (lifeCount >= 1) //one life left
    {
        glColor3f(1.0, 0.0, 0.0); // set drawing color red
        glPushMatrix();
        glTranslatef(19.0, 1.0, 0.0);
        glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
    }
    if (lifeCount >= 2) //two lives left
    {
        glColor3f(1.0, 0.0, 0.0); // set drawing color red
        glPushMatrix();
        glTranslatef(19.0, 2.0, 0.0);
        glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
    }
    if (lifeCount == 3) //three lives left
    {
        glColor3f(1.0, 0.0, 0.0); // set drawing color red
        glPushMatrix();
        glTranslatef(19.0, 3.0, 0.0);
        glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
    }

}

    //----------------------------------------------------------------------
    //Function: drawPowerUp()
    //Input: float transX, float transY
    //Output: none
    // Description:
    // Draws a single disc gold coin, at the specified location
    //----------------------------------------------------------------------
void Maze::drawPowerUp(float transX, float transY)
{
    glColor3f(0.83f, 0.68f, 0.21f); // set drawing color gold
    glPushMatrix();
    glScalef(1.0f, 1.0f, 0.25f);
    glTranslatef(transX, transY, 0.0);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
}

//----------------------------------------------------------------------
    //Function: updateCoins()
    //Input: pacman X-coordinate, pacman y-coordinate
    //Output: none
    // Description:
    // Updates if pacman has consumed a coin, powerup, or life
    //----------------------------------------------------------------------
void Maze::updateCoins(int pacmanX, int pacmanY)
{
    //remove 
    if (coinLocation[pacmanY][pacmanX] == 1)
    {
        coinLocation[pacmanY][pacmanX] = 0; //remove coin from board
        coinCount++;
    }
    if (pacmanY == 5)
    {
        if (pacmanX == 1)
        {
            if (powerupAvailable[0])
            {
                powerupAvailable[0] = 0;
                powerupMode = 1;
            }
        }
        else if (pacmanX == 17)
        {
            if (powerupAvailable[1])
            {
                powerupAvailable[1] = 0;
                powerupMode = 1;
            }
        }
    }
    else if (pacmanY == 19)
    {
        if (pacmanX == 1)
        {
            if (powerupAvailable[2])
            {
                powerupAvailable[2] = 0;
                powerupMode = 1;
            }
        }
        else if (pacmanX == 17)
        {
            if (powerupAvailable[3])
            {
                powerupAvailable[3] = 0;
                powerupMode = 1;
            }
        }
    }
}

//----------------------------------------------------------------------
    //Function: checkGameEnd()
    //Input: void
    //Output: bool TRUE if game has ended
    // Description:
    // end game if pacman wins or dies
    //----------------------------------------------------------------------
bool Maze::checkGameEnd()
{
    bool gameEndBool = 0;
    if (lifeCount < 0) //if dead
    {
        gameEndBool = 1;
    }
    else if (coinCount == 158) //if won
    {
        if ((powerupAvailable[0] + powerupAvailable[1] + powerupAvailable[2] + powerupAvailable[3]) == 0)
        {
            gameEndBool = 1;
        }
    }
    return gameEndBool;
}

//----------------------------------------------------------------------
    //Function: checkPowerupMode()
    //Input: void
    //Output: bool TRUE if Pacman has just eaten a powerup
    // Description:
    // triggers powerup mode
    //----------------------------------------------------------------------
bool Maze::checkPowerupMode()
{
    return powerupMode;
}

//----------------------------------------------------------------------
    //Function: setPowerupMode()
    //Input: TRUE if game is in PowerupMode
    //Output: void
    // Description:
    // triggers powerup mode
    //----------------------------------------------------------------------
void Maze::setPowerupMode(bool inputPowerupMode)
{
    powerupMode = inputPowerupMode;
}

//----------------------------------------------------------------------
    //Function: subtractLife()
    //Input: void
    //Output: void
    // Description:
    // subtract a life from pacman's life count
    //----------------------------------------------------------------------
void Maze::subtractLife()
{
    lifeCount -= 1;
}



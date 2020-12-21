/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30, 2020
Description:
class Pacman, which draws and moves yellow pacman graphic.
*/

#include "ECE_Pacman.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h> // Include the GLUT header file

using namespace std;

//Default Constructor
ECE_Pacman::ECE_Pacman()
{
    //Valid Move Locations
    ifstream file("Valid_Move_Location.csv");
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
            convertor >> validMoveLocation[row][col]; //store in array
        }
    }
    ifstream close();

    //Moving Decision Locations
    ifstream file2("Ghost_Decision_Location.csv");
    for (int row = 0; row < 22; ++row) //loop through each line
    {
        string line;
        getline(file2, line);
        if (!file2.good())
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
            convertor >> decisionLocation[row][col]; //store in array
        }
    }
    ifstream close();

    //set initial position
    myX = 9;
    myY = 5;
    myDirection = 1; //initially move up, which will keep pacman in place
    speedCounter = 0;
    mySpeed = 10; //pace pacman
}

//----------------------------------------------------------------------
//Function: drawPacman
//Input: none
//Output: none
// Description:
// A pacman consists of a large body sphere.
// We make extensive use of nested transformations. Everything is drawn
// relative to the origin. The body is drawn and translated
// into its final position.
//----------------------------------------------------------------------
void ECE_Pacman::drawPacman()
{
    // Draw body circle
    glColor3f(1.0f, 1.0f, 0.0f); // set drawing color to yellow
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

}

//----------------------------------------------------------------------
    //Function: resetPacman
    //Input: none
    //Output: none
    // Description:
    // reset pacman to his beginning location
    //----------------------------------------------------------------------
void ECE_Pacman::resetPacman()
{
    myX = 9;
    myY = 5;
    myDirection = 1; //initially move up, which will keep pacman in place
}

//----------------------------------------------------------------------
    //Function: updateDirection
    //Input: direction for pacman to move. 1 = N, 2 = E, 3 = S, 4 = W
    //Output: none
    // Description:
    // Updates pacman in the direction indicated by input
    //----------------------------------------------------------------------
void ECE_Pacman::updateDirection(int myNewDirection)
{
    if (decisionLocation[myY][myX] == 1)//if at an intersection
    {
        switch (myNewDirection)
        {
        case 1: //move up
            if (validMoveLocation[myY + 1][myX] == 1)
            {
                myDirection = myNewDirection;
            }
            break;
        case 2: //move right
            if (validMoveLocation[myY][myX + 1] == 1)
            {
                myDirection = myNewDirection;
            }
            break;
        case 3: //move down
            if (validMoveLocation[myY - 1][myX] == 1)
            {
                myDirection = myNewDirection;
            }
            break;
        case 4: //move left
            if (validMoveLocation[myY][myX - 1] == 1)
            {
                myDirection = myNewDirection;
            }
            break;
        }
    }
}

//----------------------------------------------------------------------
    //Function: movePacman
    //Input: none
    //Output: none
    // Description:
    // Moves pacman in the direction indicated by input
    //----------------------------------------------------------------------
void ECE_Pacman::movePacman()
{
    if (speedCounter == mySpeed)
    {
        switch (myDirection)
        {
        case 1: //move up
            if (validMoveLocation[myY + 1][myX] == 1)
            {
                myY += 1;
            }
            break;
        case 2: //move right
            if (validMoveLocation[myY][myX + 1] == 1)
            {
                myX += 1;
            }
            if (myX == 17 && myY == 11) //bridge
            {
                myX = 1;
            }
            break;
        case 3: //move down
            if (validMoveLocation[myY - 1][myX] == 1)
            {
                myY -= 1;
            }
            break;
        case 4: //move left
            if (validMoveLocation[myY][myX - 1] == 1)
            {
                myX -= 1;
            }
            if (myX == 1 && myY == 11) //bridge
            {
                myX = 17;
            }
            break;
        }
    }
    speedCounter = (speedCounter + 1) % (mySpeed + 1); //increment
}

//----------------------------------------------------------------------
    //Function: getX
    //Input: void
    //Output: current x coordinate
    // Description:
    // gets private variable for pacman's x coordinate location
    //----------------------------------------------------------------------
int ECE_Pacman::getX()
{
    return myX;
}

//----------------------------------------------------------------------
//Function: getY
//Input: void
//Output: current y coordinate
// Description:
// gets private variable for pacman's y coordinate location
//----------------------------------------------------------------------
int ECE_Pacman::getY()
{
    return myY;
}
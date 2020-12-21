/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30, 2020
Description:
class ghost, which draws and moves a ghost graphic with the specified color.
*/

#include "ECE_Ghost.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h> // Include the GLUT header file

using namespace std;

//Default Constructor
ECE_Ghost::ECE_Ghost()
{ 
    //set color to white
    colorR = 1.0;
    colorG = 1.0;
    colorB = 1.0;
    currentColorR = 1.0;
    currentColorG = 1.0;
    currentColorB = 1.0;

    //set default location to origin
    myX = 0;
    myY = 0;
    myDirection = 1; //initially move up
    speedCounter = 0;
    mySpeed = 5;
    myOrder = 1; //dummy number, red by default
    powerupMode = 0;

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
}

//Constructor
ECE_Ghost::ECE_Ghost(float inputRed, float inputGreen, float inputBlue, int startingX, int startingY, int inputOrder)
{
    //set color
    colorR = inputRed;
    colorG = inputGreen;
    colorB = inputBlue;
    currentColorR = inputRed;
    currentColorG = inputGreen;
    currentColorB = inputBlue;

    myOrder = inputOrder;

    //set location
    myX = startingX;
    myY = startingY;
    myDirection = 1; //initially moving up
    speedCounter = 0;
    mySpeed = 5;
    powerupMode = 0;

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
}


//----------------------------------------------------------------------
//Function: drawGhost
//Input: RGB colors (float R, float G, float B)
//Output: none
// Description:
// A ghost consists of a large head sphere, a body cylinder, and two eyes made with a black sphere and white disk.
//
// We make extensive use of nested transformations. Everything is drawn
// relative to the origin. The ghost's eyes are positioned
// relative to a head sphere centered at the origin. Then the head is
// translated into its final position. The body is drawn and translated
// into its final position.
//----------------------------------------------------------------------
void ECE_Ghost::drawGhost()
{
    // Draw head 
    glColor3f(currentColorR, currentColorG, currentColorB); // set drawing color, specified by input
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // Draw the body
    glPushMatrix();
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.5f, 0.5f, 0.5f, 32, 32);
    glPopMatrix();

    // Draw Eyes
    glColor3f(0.0, 0.0, 0.0); // black pupil
    glPushMatrix();
    glTranslatef(0.0f, -0.501f, 0.5f); // lift eyes to final position
    glPushMatrix();
    glTranslatef(-0.17f, 0.0f, 0.0f);
    glutSolidSphere(0.05, 10, 10); // right eye
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+0.17f, 0.0f, 0.0f);
    glutSolidSphere(0.05, 10, 10); // left eye
    glPopMatrix();
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 1.0); //white part of eye
    glPushMatrix();
    glTranslatef(0.0f, -0.501f, 0.5f); // lift eyes to final position
    glPushMatrix();
    glScalef(0.75f, 0.05f, 1.0f);
    glTranslatef(-0.2f, 0.0f, 0.0f);
    glutSolidSphere(0.15, 10, 10); // right eye
    glPopMatrix();
    glPushMatrix();
    glScalef(0.75f, 0.05f, 1.0f);
    glTranslatef(+0.2f, 0.0f, 0.0f);
    glutSolidSphere(0.15, 10, 10); // left eye
    glPopMatrix();
    glPopMatrix();
}

//----------------------------------------------------------------------
    //Function: leaveHome
    //Input: none
    //Output: none
    // Description:
    // starts ghost's movement from home base
    //
void ECE_Ghost::leaveHome()
{
    myX = 10;
    myY = 13;
}

//----------------------------------------------------------------------
    //Function: moveGhost
    //Input: pacman's x-coordinate and y-coordinate
    //Output: none
    // Description:
    // helps move the ghost in the direction of the pacman
    //
void ECE_Ghost::moveGhost(int pacmanX, int pacmanY)
{
    if (decisionLocation[myY][myX]==1)//if at an intersection
    {
        //see how far away pacman is
        int distanceX = pacmanX - myX;
        int distanceY = pacmanY - myY;

        if (abs(distanceX) > abs(distanceY)) //if ghost is closer to pacman in y-direction
        {
            if (distanceX < 0)
            {
                myDirection = 4; //move left
            }
            else
                myDirection = 2; //move right
        }
        else //if ghost is closer to pacman in x-direction
        {
            if (distanceY < 0)
            {
                myDirection = 3; //move down
            }
            else
                myDirection = 1; //move up
        }

        //choose opposite direction if in powerup mode
        //moves away from pacman
        if (powerupMode)
        {
            myDirection += 2;
            if (myDirection == 6) //mod to keep in range 1-4
            {
                myDirection = 2;
            }
            else if (myDirection == 5)
            {
                myDirection = 1;
            }
        }


        //verify move is allowed
        bool moveMade = 0;

        while (!moveMade)
        {
            switch (myDirection)
            {
            case 1: //move up
                if (validMoveLocation[myY + 1][myX] == 1)
                {
                    moveMade = 1;
                }
                break;
            case 2: //move right
                if (validMoveLocation[myY][myX + 1] == 1)
                {
                    moveMade = 1;
                }
                if (myX == 17 && myY == 11) //bridge
                {
                    moveMade = 1;
                }
                break;
            case 3: //move down
                if (validMoveLocation[myY - 1][myX] == 1)
                {
                    moveMade = 1;
                }
                break;
            case 4: //move left
                if (validMoveLocation[myY][myX - 1] == 1)
                {
                    moveMade = 1;
                }
                if (myX == 1 && myY == 11) //bridge
                {
                    moveMade = 1;
                }
                break;
            }

            if (!moveMade) //move to next direction if stuck
            {
                myDirection += 1;
                if (myDirection == 5) //mod to keep in range 1-4
                {
                    myDirection = 1;
                }
            }
        }
    }

    //move ghost forward
    if (speedCounter == mySpeed)
    {
        switch (myDirection)
        {
        case 1: //move up
            myY += 1;
            break;
        case 2: //move right
            myX += 1;
            if (myX == 17 && myY == 11) //bridge
            {
                myX = 1;
            }
            break;
        case 3: //move down
            myY -= 1;
            break;
        case 4: //move left
            myX -= 1;
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
    //Function: setPowerupMode
    //Input: TRUE to turn on powerup mode, FALSE to turn off
    //Output: none
    // Description:
    // set ghost to be in powerup mode or not
    //
void ECE_Ghost::setPowerupMode(bool inputPowerupMode)
{
    powerupMode = inputPowerupMode;

    if (powerupMode) //change color to white
    {
        currentColorR = 1.0;
        currentColorG = 1.0;
        currentColorB = 1.0;
    }
    else //change color back to original color
    {
        currentColorR = colorR;
        currentColorG = colorG;
        currentColorB = colorB;
    }
}

//----------------------------------------------------------------------
    //Function: getX
    //Input: void
    //Output: current x coordinate
    // Description:
    // gets private variable for ghost's x coordinate location
    //----------------------------------------------------------------------
int ECE_Ghost::getX()
{
    return myX;
}

//----------------------------------------------------------------------
//Function: getY
//Input: void
//Output: current y coordinate
// Description:
// gets private variable for ghost's y coordinate location
//----------------------------------------------------------------------
int ECE_Ghost::getY()
{
    return myY;
}

//----------------------------------------------------------------------
    //Function: setLocation
    //Input: int x, int y
    //Output: void
    // Description:
    // set ghost location
    //----------------------------------------------------------------------
void ECE_Ghost::setLocation(int x, int y)
{
    myX = x;
    myY = y;
    myDirection = 1; //direction up by default
}



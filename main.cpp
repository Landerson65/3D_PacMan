/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30 , 2020
Description:
This project uses OpenGL to recreate the parts necessary for a Pacman Game and openMP to manage ghosts.
It mimics the pacman game like this: http://www.freewebarcade.com/game/3d-pacman/
*/

#include <iostream>
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include "ECE_Ghost.h"
#include "ECE_Pacman.h"
#include "Maze.h"
#include <thread>
#include <ctime>
#include <omp.h>

#define ESC 27

//----------------------------------------------------------------------
// Global variables
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. 
//----------------------------------------------------------------------

bool gameInProgress = 0; //flag to start game
int powerupModeCounter = 0; //counts how many times you've looped through while in powerup mode
clock_t powerupModeTimer; //helps count to 5 seconds

//flags to tell ghosts in threads to return home
bool redResetFlag = 0;
bool pinkResetFlag = 0;
bool blueResetFlag = 0;
bool orangeResetFlag = 0;
//flag to tell ghosts have died
bool redDiedFlag = 0;
bool pinkDiedFlag = 0;
bool blueDiedFlag = 0;
bool orangeDiedFlag = 0;

// Camera position
float x = 25.0, y = -15, z = 20; 

// Camera direction
float lx = 25.0, ly = -15;

//Declare ghosts, pacman, and maze
ECE_Ghost redGhost(1.0f, 0.0f, 0.0f, 9, 13, 1);
ECE_Ghost pinkGhost(1.0f, 0.72f, 1.0f, 9, 11, 2);
ECE_Ghost blueGhost(0.0f, 1.0f, 1.0f, 8, 11, 3);
ECE_Ghost orangeGhost(1.0f, 0.72f, 0.32f, 10, 11, 4);
ECE_Pacman myPacman;
Maze myMaze;

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void)
{
    glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// Draw the entire scene
//----------------------------------------------------------------------
void renderScene(void)
{
    // Clear color and depth buffers
    glClearColor(0.0, 0.0, 0.0, 0.0); // sky color is black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set the camera centered at (x,y,z) and looking along directional
    // vector (9, 11, 0), with the z-axis pointing up
    gluLookAt(
        lx, ly, z,
        9.0, 11.0, 0.0,
        0.0, 0.0, 1.0);

    // Draw ghosts
    glPushMatrix(); //red
    glTranslatef((float)(redGhost.getX()), (float)(redGhost.getY()), 0);
    redGhost.drawGhost();
    glPopMatrix(); //pink
    glPushMatrix();
    glTranslatef((float)(pinkGhost.getX()), (float)(pinkGhost.getY()), 0);
    pinkGhost.drawGhost();
    glPopMatrix(); //blue
    glPushMatrix();
    glTranslatef((float)(blueGhost.getX()), (float)(blueGhost.getY()), 0);
    blueGhost.drawGhost();
    glPopMatrix(); //orange
    glPushMatrix();
    glTranslatef((float)(orangeGhost.getX()), (float)(orangeGhost.getY()), 0);
    orangeGhost.drawGhost();
    //draw pacman
    myPacman.movePacman();
    glPopMatrix();
    glPushMatrix();
    glTranslatef((float)(myPacman.getX()), (float)(myPacman.getY()), 0);
    myPacman.drawPacman();
    //update and draw maze
    myMaze.updateCoins(myPacman.getX(), myPacman.getY());//see how pacman's moves changed the board
    glPopMatrix();
    glPushMatrix();
    myMaze.drawMaze();
    glPopMatrix();
    //check for powerup mode
    if (myMaze.checkPowerupMode())
    {
        if (powerupModeCounter == 0) //only set the first time through
        {
            //5 second timer
            powerupModeTimer = clock() + 5 * CLOCKS_PER_SEC;

            //trigger color change and direction change for ghosts
            redGhost.setPowerupMode(TRUE);
            pinkGhost.setPowerupMode(TRUE);
            blueGhost.setPowerupMode(TRUE);
            orangeGhost.setPowerupMode(TRUE);
        }
        powerupModeCounter++;

        if (powerupModeTimer < clock()) //once 5 seconds has passed
        {
            //end powerup mode
            redGhost.setPowerupMode(FALSE);
            pinkGhost.setPowerupMode(FALSE);
            blueGhost.setPowerupMode(FALSE);
            orangeGhost.setPowerupMode(FALSE);
            myMaze.setPowerupMode(FALSE);
            powerupModeCounter = 0;
        }
    }

    //check if pacman loses a life
    if (myPacman.getX() == redGhost.getX() && myPacman.getY() == redGhost.getY()) //red and pacman intersect
    {
        if (!myMaze.checkPowerupMode()) //if ghosts are hunters
        {
            myMaze.subtractLife(); //pacman dies
            myPacman.resetPacman();
            redResetFlag = 1;
            pinkResetFlag = 1;
            blueResetFlag = 1;
            orangeResetFlag = 1;
        }
        else //if pacman is hunter
        {
            redDiedFlag = 1; //ghost dies
        }
    }
    else if (myPacman.getX() == pinkGhost.getX() && myPacman.getY() == pinkGhost.getY()) //pink and pacman intersect
    {
        if (!myMaze.checkPowerupMode()) //if ghosts are hunters
        {
            myMaze.subtractLife(); //pacman dies
            myPacman.resetPacman();
            redResetFlag = 1;
            pinkResetFlag = 1;
            blueResetFlag = 1;
            orangeResetFlag = 1;
        }
        else //if pacman is hunter
        {
            pinkDiedFlag = 1; //ghost dies
        }
    }
    else if (myPacman.getX() == blueGhost.getX() && myPacman.getY() == blueGhost.getY()) //blue and pacman intersect
    {
        if (!myMaze.checkPowerupMode()) //if ghosts are hunters
        {
        myMaze.subtractLife(); //pacman dies
        myPacman.resetPacman();
        redResetFlag = 1;
        pinkResetFlag = 1;
        blueResetFlag = 1;
        orangeResetFlag = 1;
        }
        else //if pacman is hunter
        {
            blueDiedFlag = 1; //ghost dies
        }
    }
    else if (myPacman.getX() == orangeGhost.getX() && myPacman.getY() == orangeGhost.getY()) //orange and pacman intersect
    {
        if (!myMaze.checkPowerupMode()) //if ghosts are hunters
        {
            myMaze.subtractLife(); //pacman dies
            myPacman.resetPacman();
            redResetFlag = 1;
            pinkResetFlag = 1;
            blueResetFlag = 1;
            orangeResetFlag = 1;
        }
        else //if pacman is hunter
        {
            orangeDiedFlag = 1; //ghost dies
        }
    }

    //check for end of game (pacman eats all coins/powerups or dies)
    if (myMaze.checkGameEnd())
    {
        exit(0); //exit game
    }

    glutSwapBuffers(); // Make it all visible
}

//----------------------------------------------------------------------
    //Function: redGhostLoopFunc
    //Input: void
    //Output: void
    // Description:
    // handle the red ghost in the thread
    //----------------------------------------------------------------------
void redGhostLoopFunc()
{
    clock_t endwait;
    //red ghost leaves home immeidately
    redGhost.leaveHome();
    while (gameInProgress)
    {
        endwait = clock() + 0.1 * CLOCKS_PER_SEC; //pace ghost
        while (clock() < endwait) {}
        //move ghost
        redGhost.moveGhost(myPacman.getX(), myPacman.getY());
        //if pacman has died, reset
        if (redResetFlag) 
        {
            redGhost.leaveHome();
            redResetFlag = 0;
        }
        //if ghost has died, wait 5 seconds and reset
        if (redDiedFlag)
        {
            redGhost.setLocation(9, 13);
            endwait = clock() + 5 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            redGhost.leaveHome();
            redDiedFlag = 0;
        }
    }
}

//----------------------------------------------------------------------
    //Function: pinkGhostLoopFunc
    //Input: void
    //Output: void
    // Description:
    // handle the pink ghost in the thread
    //----------------------------------------------------------------------
void pinkGhostLoopFunc()
{
    //wait 2 seconds to release pink ghost
    clock_t endwait;
    endwait = clock() + 2 * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
    pinkGhost.leaveHome();
    //periodically move ghost
    while (gameInProgress)
    {
        endwait = clock() + 0.1 * CLOCKS_PER_SEC; //pace ghost
        while (clock() < endwait) {}
        //move ghost
        pinkGhost.moveGhost(myPacman.getX(), myPacman.getY());
        if (pinkResetFlag) //if pacman has died, reset
        {
            pinkGhost.setLocation(9, 11);
            endwait = clock() + 2 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            pinkGhost.leaveHome();
            pinkResetFlag = 0;
        }
        //if ghost has died, wait 5 seconds and reset
        if (pinkDiedFlag)
        {
            pinkGhost.setLocation(9, 11);
            endwait = clock() + 5 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            pinkGhost.leaveHome();
            pinkDiedFlag = 0;
        }
    }
}

//----------------------------------------------------------------------
    //Function: blueGhostLoopFunc
    //Input: void
    //Output: void
    // Description:
    // handle the blue ghost in the thread
    //----------------------------------------------------------------------
void blueGhostLoopFunc()
{
    //wait 4 seconds to release pink ghost
    clock_t endwait;
    endwait = clock() + 4 * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
    blueGhost.leaveHome();
    //periodically move ghost
    while (gameInProgress)
    {
        endwait = clock() + 0.1 * CLOCKS_PER_SEC; //pace ghost
        while (clock() < endwait) {}
        //move ghost
        blueGhost.moveGhost(myPacman.getX(), myPacman.getY());
        if (blueResetFlag) //if pacman has died, reset
        {
            blueGhost.setLocation(8, 11);
            endwait = clock() + 4 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            blueGhost.leaveHome();
            blueResetFlag = 0;
        }
        //if ghost has died, wait 5 seconds and reset
        if (blueDiedFlag)
        {
            blueGhost.setLocation(8, 11);
            endwait = clock() + 5 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            blueGhost.leaveHome();
            blueDiedFlag = 0;
        }
    }
}

//----------------------------------------------------------------------
    //Function: orangeGhostLoopFunc
    //Input: void
    //Output: void
    // Description:
    // handle the pink ghost in the thread
    //----------------------------------------------------------------------
void orangeGhostLoopFunc()
{
    //wait 6 seconds to release orange ghost
    clock_t endwait;
    endwait = clock() + 6 * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
    orangeGhost.leaveHome();
    //periodically move ghost
    while (gameInProgress)
    {
        endwait = clock() + 0.1 * CLOCKS_PER_SEC; //pace ghost
        while (clock() < endwait) {}
        //move ghost
        orangeGhost.moveGhost(myPacman.getX(), myPacman.getY());
        if (orangeResetFlag) //if pacman has died, reset
        {
            orangeGhost.setLocation(10, 11);
            endwait = clock() + 6 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            orangeGhost.leaveHome();
            orangeResetFlag = 0;
        }
        //if ghost has died, wait 5 seconds and reset
        if (orangeDiedFlag)
        {
            orangeGhost.setLocation(10, 11);
            endwait = clock() + 5 * CLOCKS_PER_SEC;
            while (clock() < endwait) {}
            orangeGhost.leaveHome();
            orangeDiedFlag = 0;
        }
    }
}


//----------------------------------------------------------------------
// User-input callbacks
//
// processNormalKeys: ESC, q, and Q cause program to exit
// pressSpecialKey: Up arrow = forward motion, down arrow = backwards
//----------------------------------------------------------------------
void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == ESC || key == 'q' || key == 'Q')
    {
        exit(0);
    }
}

void pressSpecialKey(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        myPacman.updateDirection(1);
        break;
    case GLUT_KEY_RIGHT:
        myPacman.updateDirection(2);
        break;
    case GLUT_KEY_DOWN: 
        myPacman.updateDirection(3);
        break;
    case GLUT_KEY_LEFT:
        myPacman.updateDirection(4);
        break;
    }
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char** argv)
{
    printf("\n\
-----------------------------------------------------------------------\n\
  Instructions to Lillian's Pacman Game:\n\
  - Move pacman using the arrow keys\n\
  - Collect all the coins and powerups to win\n\
  - Avoid the ghosts... you only have 3 lives\n\
  - q or ESC to quit\n\
  \n\
  Good Luck!\n\
-----------------------------------------------------------------------\n");

    //Wait for any key press to start the game
    system("pause");

    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Lillian's 3D Pacman Game");
    glEnable(GL_DEPTH_TEST);
    // register callbacks
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    gameInProgress = 1;
    //create threads for each ghost
    std::thread red_ghost_thread(redGhostLoopFunc);
    std::thread pink_ghost_thread(pinkGhostLoopFunc);
    std::thread blue_ghost_thread(blueGhostLoopFunc);
    std::thread orange_ghost_thread(orangeGhostLoopFunc);
    glutIdleFunc(update); // incremental update
    glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
    glutKeyboardFunc(processNormalKeys); // process standard key clicks
    glutSpecialFunc(pressSpecialKey); // process special key pressed
    
    // enter GLUT event processing cycle
    glutMainLoop();

    return 0; // this is just to keep the compiler happy
}
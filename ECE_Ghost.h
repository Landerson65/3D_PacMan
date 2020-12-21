/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30, 2020
Description:
Header file for class ghost, which draws and moves a ghost graphic with the specified color.
*/

#pragma once

class ECE_Ghost
{
public:
	//constructors
	ECE_Ghost();
	ECE_Ghost(float inputRed, float inputGreen, float inputBlue, int startingX, int startingY, int inputOrder);

	//----------------------------------------------------------------------
	//Function: drawGhost
	//Input: RGB colors (float R, float G, float B, int x, int y, int order)
	//Output: none
	// Description:
	// A ghost consists of a large head sphere, a body cylinder, and two eyes made with a black sphere and white disk.
	//
	void drawGhost();

	//----------------------------------------------------------------------
	//Function: leaveHome
	//Input: none
	//Output: none
	// Description:
	// starts ghost's movement from home base
	//
	void leaveHome();

	//----------------------------------------------------------------------
	//Function: moveGhost
	//Input: pacman's x-coordinate and y-coordinate
	//Output: none
	// Description:
	// helps move the ghost in the direction of the pacman
	//
	void moveGhost(int pacmanX, int pacmanY);

	//----------------------------------------------------------------------
	//Function: setPowerupMode
	//Input: TRUE to turn on powerup mode, FALSE to turn off
	//Output: none
	// Description:
	// set ghost to be in powerup mode or not
	//
	void setPowerupMode(bool inputPowerupMode);

	//----------------------------------------------------------------------
	//Function: getX
	//Input: void
	//Output: current x coordinate
	// Description:
	// gets private variable for ghost's x coordinate location
	//----------------------------------------------------------------------
	int getX();

	//----------------------------------------------------------------------
	//Function: getY
	//Input: void
	//Output: current y coordinate
	// Description:
	// gets private variable for ghost's y coordinate location
	//----------------------------------------------------------------------
	int getY();

	//----------------------------------------------------------------------
	//Function: setLocation
	//Input: int x, int y
	//Output: void
	// Description:
	// set ghost location
	//----------------------------------------------------------------------
	void setLocation(int x, int y);



private:
	//RGB colors for the ghosts
	float colorR; //remember color for powerupMode
	float colorG;
	float colorB;
	float currentColorR; //current color
	float currentColorG;
	float currentColorB;

	//locations the ghosts can move in the maze
	float validMoveLocation[22][19];
	//locations to change direction in the maze
	float decisionLocation[22][19];
	//current coordinate
	int myX;
	int myY;
	int myDirection; //1 = up, 2 = right, 3 = down, 4 = left 
	//help control speed of ghost
	int speedCounter;
	int mySpeed;
	int myOrder; //order of events 
	bool powerupMode; //TRUE if in powerup mode

};


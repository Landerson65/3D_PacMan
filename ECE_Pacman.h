/*
Author: Lillian Anderson
Class: ECE 6122
Last Date Modified: November 30, 2020
Description:
Header file for class Pacman, which draws and moves yellow pacman graphic.
*/

#pragma once
class ECE_Pacman
{
public:
	//constructors
	ECE_Pacman();

	//----------------------------------------------------------------------
	//Function: drawPacman
	//Input: none
	//Output: none
	// Description:
	// A pacman consists of a large body sphere.
	//----------------------------------------------------------------------
	void drawPacman();

	//----------------------------------------------------------------------
	//Function: movePacman
	//Input: none
	//Output: none
	// Description:
	// Moves pacman in the direction indicated by input
	//----------------------------------------------------------------------
	void movePacman();

	//----------------------------------------------------------------------
	//Function: resetPacman
	//Input: none
	//Output: none
	// Description:
	// reset pacman to his beginning location
	//----------------------------------------------------------------------
	void resetPacman();

	//----------------------------------------------------------------------
	//Function: updateDirection
	//Input: direction for pacman to move. 1 = N, 2 = E, 3 = S, 4 = W
	//Output: none
	// Description:
	// Updates pacman in the direction indicated by input
	//----------------------------------------------------------------------
	void updateDirection(int myNewDirection);

	//----------------------------------------------------------------------
	//Function: getX
	//Input: void
	//Output: current x coordinate
	// Description:
	// gets private variable for pacman's x coordinate location
	//----------------------------------------------------------------------
	int getX();

	//----------------------------------------------------------------------
	//Function: getY
	//Input: void
	//Output: current y coordinate
	// Description:
	// gets private variable for pacman's y coordinate location
	//----------------------------------------------------------------------
	int getY();

private:
	float validMoveLocation[22][19]; //locations the ghosts can move in the maze
	float decisionLocation[22][19]; //locations to change direction in maze
	//current coordinates
	int myX;
	int myY;
	int myDirection; //1 = up, 2 = right, 3 = down, 4 = left
	//help pace pacman
	int speedCounter;
	int mySpeed;
};

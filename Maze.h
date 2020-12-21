/*
Author: Lillian Anderson
Class: ECE6122
Last Date Modified: November 30, 2020
Description:
Header file for class Maze, which draws the maze walls, coins, and power ups.
*/

#pragma once
class Maze
{
public:
	//Default Constructor
	Maze();

	//----------------------------------------------------------------------
	//Function: drawMaze()
	//Input: none
	//Output: none
	// Description:
	// Draws the initial board setup, with maze, coins, and power ups
	//----------------------------------------------------------------------
	void drawMaze();

	//----------------------------------------------------------------------
	//Function: updateCoins()
	//Input: pacman X-coordinate, pacman y-coordinate
	//Output: none
	// Description:
	// Updates if pacman has consumed a coin, powerup, or life
	//----------------------------------------------------------------------
	void updateCoins(int pacmanX, int pacmanY);

	//----------------------------------------------------------------------
	//Function: checkGameEnd()
	//Input: void
	//Output: bool TRUE if game has ended
	// Description:
	// end game if pacman wins or dies
	//----------------------------------------------------------------------
	bool checkGameEnd();

	//----------------------------------------------------------------------
	//Function: checkPowerupMode()
	//Input: void
	//Output: bool TRUE if Pacman has just eaten a powerup
	// Description:
	// checks powerup mode
	//----------------------------------------------------------------------
	bool checkPowerupMode();

	//----------------------------------------------------------------------
	//Function: setPowerupMode()
	//Input: TRUE if game is in PowerupMode
	//Output: void
	// Description:
	// triggers powerup mode
	//----------------------------------------------------------------------
	void setPowerupMode(bool inputPowerupMode);

	//----------------------------------------------------------------------
	//Function: subtractLife()
	//Input: void
	//Output: void
	// Description:
	// subtract a life from pacman's life count
	//----------------------------------------------------------------------
	void subtractLife();

private:

	//----------------------------------------------------------------------
	//Function: drawWall()
	//Input: (float length, float transX, float transY, float rotateX, float rotateY)
	//Output: none
	// Description:
	// Draws a single cylindrical blue wall for the maze, at the specified location
	//----------------------------------------------------------------------
	void drawWall(float length, float transX, float transY, float rotateX, float rotateY);

	//----------------------------------------------------------------------
	//Function: drawVertex()
	//Input: float transX, float transY
	//Output: none
	// Description:
	// Draws a single small blue sphere to make the maze vertices smooth, at the specified location
	//----------------------------------------------------------------------
	void drawVertex(float transX, float transY);

	//----------------------------------------------------------------------
	//Function: drawCoin()
	//Input: float transX, float transY
	//Output: none
	// Description:
	// Draws a single spherical silver coin, at the specified location
	//----------------------------------------------------------------------
	void drawCoin(float transX, float transY);

	//----------------------------------------------------------------------
	//Function: drawAllCoins()
	//Input: none
	//Output: none
	// Description:
	// Draws all of the coins and power ups based off of locations in array coinLocation
	//----------------------------------------------------------------------
	void drawAllCoins();

	//----------------------------------------------------------------------
	//Function: drawPowerUp()
	//Input: float transX, float transY
	//Output: none
	// Description:
	// Draws a single disc gold coin, at the specified location
	//----------------------------------------------------------------------
	void drawPowerUp(float transX, float transY);

	//Locations of coins and powerups
	float coinLocation[22][19];
	bool powerupAvailable[4]; //True if the powerup is available. Numbered left to right, bottom to top.
	bool powerupMode; //TRUE if pacman is hunter
	int coinCount; //number of coins collected
	int lifeCount; //number of lives left

};


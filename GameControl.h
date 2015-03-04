#ifndef GAMECONTROL_H_
#define GAMECONTROL_H_
#include "Universal.h"
#include "Bricks.h"
#include "TetrisWorld.h"
#define NULL 0

class GameControl
{
	// Currently Active Brick
	Brick* curBrick;
	// Next Active Brick
	Brick* nextBrick;
	// User Interface
	TetrisWorld world;
	// Score Counter
	int score;
	// The Milliseconds of Sleep Function (Determine the Refresh Period)
	const int refreshPeriod;

	// Display Welcome Interface
	void welcome () const;
	// Get A Brick With Random Type And Random Status
	Brick* getRandBrick () const;
	// Check Keyboard Input
	Command getChoice () const;
	// Check If the Brick Is Out of Boundary
	bool isOutOfBoundary () const;
	// Check If the Brick Is Collision With Settled Blocks or the Bottom
	bool isCollision () const;
	// Process the Settlement And Next Brick Creation
	void arrangeProcess ();
	// Settle the Brick And Build A New One
	void settle ();
	// Clear the Filled Row
	void eliminate ();
public:
	GameControl (): world(20,20), refreshPeriod(600), score(0) { nextBrick = curBrick = NULL; }
	~GameControl () { if ( curBrick != NULL ) delete curBrick; if ( nextBrick != NULL ) delete nextBrick; }

	// Main Body of Game
	void run ();
	// Reset the Game
	void reset ();
	// Refresh the Screen And Print
	void refresh ();
};

#endif
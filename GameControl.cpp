#include "GameControl.h"
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
Brick* GameControl::getRandBrick () const
{
	// 7 Type Of Brick
	int type = rand () % 7;
	Brick* brick = NULL;
	switch ( type )
	{
	case 0:
		brick = new Brick_O (world.aSize/2,1); break;
	case 1:
		brick = new Brick_I (world.aSize/2,1); break;
	case 2:
		brick = new Brick_Z (world.aSize/2,1); break;
	case 3:
		brick = new Brick_S (world.aSize/2,1); break;
	case 4:
		brick = new Brick_T (world.aSize/2,1); break;
	case 5:
		brick = new Brick_L (world.aSize/2,1); break;
	case 6:
		brick = new Brick_J (world.aSize/2,1); break;
	}
	return brick;
}
void GameControl::welcome () const
{
	for ( int row = 0; row <= world.vSize+1; ++row )
	{
		putchar (' ');
		for ( int col = 0; col <= world.aSize+1; ++col )
			if ( row == world.vSize/2-3 && col == world.aSize/2-5 )
			{
				printf ("T E T R I S");
				col += 10;
				continue;
			}
			else if ( row == world.vSize/2+3 && col == world.aSize/2-8 )
			{
				printf ("Press R to Start!");
				col += 16;
				continue;
			}
			else
				putchar (world.screen[row][col]);
		putchar ('\n');
	}
	
	while ( getChoice() != Restart );

}
void GameControl::run ()
{
	// Initialize
	srand (time(0));
	welcome ();
	curBrick = getRandBrick ();
	nextBrick = getRandBrick ();
	refresh ();

	// Infinite Loop
	while ( true )
	{
		// Get User's Command
		Command key = getChoice();
		// Feel Free to Exit
		if ( key == Exit )
			return;
		// Restart A New Game At Any Time
		if ( key == Restart )
		{
			reset ();
			curBrick = getRandBrick ();
			nextBrick = getRandBrick ();
			refresh ();
			continue;
		}
		// Move the Brick According to the Command
		if ( key != None )
		{
			curBrick->move (key);
			// Backtrace When Illegal Movement Takes Place
			if ( isOutOfBoundary () || isCollision () )
			{
				curBrick->backLastStatus (key);
				// Falling Collision (Need to Settle Down)
				if ( key == Fall )
				{
					arrangeProcess ();
					if ( isCollision () )
						return;
				}
			}
			refresh ();
			continue;
		}
		// Fall Every Period
		curBrick->fall ();
		// Falling Collision (Need to Settle Down)
		if ( isCollision () )
		{
			curBrick->backLastStatus (Fall);
			arrangeProcess ();
			if ( isCollision () )
				return;
		}
		refresh ();
		Sleep (refreshPeriod);
	}
}
Command GameControl::getChoice () const
{
	Command com = None;
	if ( _kbhit() )
	{
		char ch = _getch();
		switch (ch)
		{
		// Press d to Right
		case 100: com = Right; break;
		// Press w to Rotate
		case 119: com = Rotate; break;
		// Press a to Left
		case 97: com = Left; break;
		// Press s to Arrange
		case 115: com = Fall; break;
		// Press p to exit
		case 'q': com = Exit; break;
		// Press r to restart
		case 'r': com = Restart; break;
		}
	}
	return com;
}
bool GameControl::isOutOfBoundary () const
{
	for ( int i = 0; i < 4; ++i )
		// Out of Left or Right Frame
		if ( curBrick->blocks[i].getX() <= 0 || curBrick->blocks[i].getX() > world.aSize )
			return true;
	return false;
}
bool GameControl::isCollision () const
{
	for ( int i = 0; i < 4; ++i )
	{
		// Floor Collision
		if ( curBrick->blocks[i].getY() > world.vSize )
			return true;
		// Settled Brick Collision
		if ( world.screen[curBrick->blocks[i].getY()][curBrick->blocks[i].getX()] == '*' )
			return true;
	}
	return false;
}
void GameControl::arrangeProcess ()
{
	// Settle the Brick
	settle ();
	refresh ();
	Sleep (refreshPeriod);

	// Eliminate the Full Row
	eliminate ();
	delete curBrick;
	curBrick = nextBrick;
	nextBrick = getRandBrick();
	refresh ();
	Sleep (refreshPeriod);
}
void GameControl::settle ()
{
	// Put Current Brick's Data to the Screen Map
	for ( int i = 0; i < 4; ++i )
		world.screen[curBrick->blocks[i].getY()][curBrick->blocks[i].getX()] = '*';
}
void GameControl::eliminate ()
{
	// Bouns When Eliminate More Than One Row
	int bonus = 0;
	for ( int i = 0; i < 4; ++i )
	{
		// Check If Elimination Is Needed
		bool needClearing = true;
		int brickRow = curBrick->blocks[i].getY();
		for ( int j = 1; j <= world.aSize; ++j )
			if ( world.screen[brickRow][j] != '*' )
			{
				needClearing = false;
				break;
			}
		if ( needClearing )
		{
			// Score!
			score += (++ bonus)*100;
			// Move All the Upside Data
			for ( int row = brickRow-1; row > 0; --row )
				for ( int j = 1; j <= world.aSize; ++j )
					world.screen[row+1][j] = world.screen[row][j];
			for ( int j = 1; j <= world.aSize; ++j )
				world.screen[1][j] = ' ';
		}
	}
}
void GameControl::refresh ()
{
	world.clear ();
	world.print (curBrick,nextBrick,score);
}
void GameControl::reset ()
{
	if ( curBrick != NULL )
		delete curBrick;
	curBrick = NULL;
	if ( nextBrick != NULL )
		delete nextBrick;
	nextBrick = NULL;

	world.reset ();
}
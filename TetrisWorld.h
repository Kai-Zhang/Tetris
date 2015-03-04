#ifndef TETRISWORLD_H_
#define TETRISWORLD_H_
#include "Universal.h"

class TetrisWorld
{
	// Screen Align Length
	const int aSize;
	// Screen Vertical Length
	const int vSize;
	// Screen buffer
	char** screen;
public:
	TetrisWorld (int = 20, int = 20);
	~TetrisWorld ();
	// Clear the Screen
	void clear () const;
	// Paint the Screen
	void print (Brick*, Brick*, int) const;
	// Reset the Screen Buffer
	void reset ();
	
	friend GameControl;
};

#endif
#ifndef BRICKS_H_
#define BRICKS_H_
#include "Universal.h"
#include "Block.h"
#include <cstdlib>
#include <ctime>

class Brick
{
protected:
	// Blocks in Brick
	// Each Block Numbered From Left to Right And From Top to Bottom
	Block blocks [4];

	// Rotation Status
	enum Status {Head, Right, Tail, Left} status;
	// Initialize the Status
	Status randstatus () { return (Status)(rand() % 4); }
	// Backtrace
	virtual void backLastStatus (Command);
public:
	Brick () { status = randstatus (); }
	Brick (const Brick& b) { for ( int i=0; i < 4; ++i ) blocks[i] = b.blocks[i]; }
	virtual ~Brick () { }

	// Rotate the Brick (Pure Virtual Function)
	virtual void rotate () = 0;
	// Make the Brick Fall Down
	virtual void fall () { for ( int i=0; i < 4; ++i ) blocks[i].moveDown(); }
	
	// Move the Brick With Provided Direction
	virtual void move (Command);

	Brick& operator = (const Brick& b) { for ( int i=0; i < 4; ++i ) blocks[i] = b.blocks[i]; return *this; }

	friend TetrisWorld;
	friend GameControl;
};

class Brick_O: public Brick
{
public:
	Brick_O (int = 10, int = 0);
	~Brick_O () { }

	void rotate () { }
};
class Brick_I: public Brick
{
public:
	Brick_I (int = 10, int = 0);
	~Brick_I () { }

	void rotate ();
};
class Brick_Z: public Brick
{
public:
	Brick_Z (int = 10, int = 0);
	~Brick_Z () { }

	void rotate ();
};
class Brick_S: public Brick
{
public:
	Brick_S (int = 10, int = 0);
	~Brick_S () { }

	void rotate ();
};
class Brick_T: public Brick
{
public:
	Brick_T (int = 10, int = 0);
	~Brick_T () { }

	void rotate ();
};
class Brick_L: public Brick
{
public:
	Brick_L (int = 10, int = 0);
	~Brick_L () { }

	void rotate ();
};
class Brick_J: public Brick
{
public:
	Brick_J (int = 10, int = 0);
	~Brick_J () { }

	void rotate ();
};

#endif
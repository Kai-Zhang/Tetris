#include "Bricks.h"
#include <iostream>

void Brick::move (Command c)
{
	switch ( c )
	{
	case Command::Right:
		blocks[0].moveRight();
		blocks[1].moveRight();
		blocks[2].moveRight();
		blocks[3].moveRight();
		break;
	case Command::Left:
		blocks[0].moveLeft();
		blocks[1].moveLeft();
		blocks[2].moveLeft();
		blocks[3].moveLeft();
		break;
	case Command::Rotate:
		rotate ();
	case Command::Fall:
		fall ();
	}
}
void Brick::backLastStatus (Command c)
{
	switch ( c )
	{
	case Command::Right:
		blocks[0].moveLeft();
		blocks[1].moveLeft();
		blocks[2].moveLeft();
		blocks[3].moveLeft();
		break;
	case Command::Left:
		blocks[0].moveRight();
		blocks[1].moveRight();
		blocks[2].moveRight();
		blocks[3].moveRight();
		break;
	case Command::Rotate:
		rotate (); rotate(); rotate();
		break;
	case Command::Fall:
		blocks[0].moveUp();
		blocks[1].moveUp();
		blocks[2].moveUp();
		blocks[3].moveUp();
	}
}
Brick_O::Brick_O (int x, int y)
{
	blocks[0].setLocation (x,y);	// 0 1
	blocks[1].setLocation (x+1,y);	// 2 3
	blocks[2].setLocation (x,y+1);
	blocks[3].setLocation (x+1,y+1);
}
Brick_I::Brick_I (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head: case Tail:						// 0
		blocks[1].setLocation (x,y+1);			// 1
		blocks[2].setLocation (x,y+2);			// 2
		blocks[3].setLocation (x,y+3); break;	// 3
	case Left: case Right:
		blocks[1].setLocation (x+1,y);			// 0 1 2 3
		blocks[2].setLocation (x+2,y);
		blocks[3].setLocation (x+3,y); break;
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_I::rotate ()
{
	switch ( status )
	{
	case Head: case Tail:
		blocks[0].moveDown(); blocks[0].moveDown(); blocks[0].moveLeft(); blocks[0].moveLeft();
		blocks[1].moveDown(); blocks[1].moveLeft();
		blocks[3].moveUp(); blocks[3].moveRight();
		break;
	case Left: case Right:
		blocks[0].moveRight(); blocks[0].moveRight(); blocks[0].moveUp(); blocks[0].moveUp();
		blocks[1].moveRight(); blocks[1].moveUp();
		blocks[3].moveLeft(); blocks[3].moveDown();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
Brick_Z::Brick_Z (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head: case Tail:
		blocks[1].setLocation (x-1,y+1);			//   0
		blocks[2].setLocation (x,y+1);			// 1 2
		blocks[3].setLocation (x-1,y+2); break;	// 3
	case Left: case Right:
		blocks[1].setLocation (x+1,y);			// 0 1
		blocks[2].setLocation (x+1,y+1);		//   2 3
		blocks[3].setLocation (x+2,y+1); break;
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_Z::rotate ()
{
	switch ( status )
	{
	case Head: case Tail:
		blocks[0].moveDown(); blocks[0].moveLeft(); blocks[0].moveLeft();
		blocks[2].moveLeft(); blocks[2].moveDown();
		blocks[3].moveRight();
		break;
	case Left: case Right:
		blocks[0].moveRight(); blocks[0].moveRight(); blocks[0].moveUp();
		blocks[2].moveUp(); blocks[2].moveRight();
		blocks[3].moveLeft();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
Brick_S::Brick_S (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head: case Tail:
		blocks[1].setLocation (x,y+1);			// 0
		blocks[2].setLocation (x+1,y+1);		// 1 2
		blocks[3].setLocation (x+1,y+2); break;	//   3
	case Left: case Right:
		blocks[1].setLocation (x+1,y);			//   0 1
		blocks[2].setLocation (x-1,y+1);			// 2 3
		blocks[3].setLocation (x,y+1); break;
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_S::rotate ()
{
	switch ( status )
	{
	case Head: case Tail:
		blocks[0].moveDown(); blocks[0].moveRight();
		blocks[1].moveRight(); blocks[1].moveRight();
		blocks[2].moveDown(); blocks[2].moveLeft();
		break;
	case Left: case Right:
		blocks[0].moveLeft(); blocks[0].moveUp();
		blocks[1].moveLeft(); blocks[1].moveLeft();
		blocks[2].moveUp(); blocks[2].moveRight();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
Brick_T::Brick_T (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head:
		blocks[1].setLocation (x-1,y+1);			//   0
		blocks[2].setLocation (x,y+1);			// 1 2 3
		blocks[3].setLocation (x+1,y+1); break;
	case Right:
		blocks[1].setLocation (x,y+1);			// 0
		blocks[2].setLocation (x+1,y+1);		// 1 2
		blocks[3].setLocation (x,y+2); break;	// 3
	case Tail:
		blocks[1].setLocation (x+1,y);			// 0 1 2
		blocks[2].setLocation (x+2,y);			//   3
		blocks[3].setLocation (x+1,y+1); break;
	case Left:
		blocks[1].setLocation (x-1,y+1);			//   0
		blocks[2].setLocation (x,y+1);			// 1 2
		blocks[3].setLocation (x,y+2); break;	//   3
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_T::rotate ()
{
	switch ( status )
	{
	case Head:
		blocks[1].moveRight();
		blocks[2].moveRight();
		blocks[3].moveLeft(); blocks[3].moveDown();
		break;
	case Right:
		blocks[0].moveDown(); blocks[0].moveLeft();
		break;
	case Tail:
		blocks[0].moveRight(); blocks[0].moveUp();
		blocks[1].moveLeft();
		blocks[2].moveLeft();
		break;
	case Left:
		blocks[3].moveUp(); blocks[3].moveRight();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
Brick_L::Brick_L (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head:
		blocks[1].setLocation (x,y+1);			// 0
		blocks[2].setLocation (x,y+2);			// 1
		blocks[3].setLocation (x+1,y+2); break;	// 2 3
	case Right:
		blocks[1].setLocation (x+1,y);			// 0 1 2
		blocks[2].setLocation (x+2,y);			// 3
		blocks[3].setLocation (x,y+1); break;
	case Tail:
		blocks[1].setLocation (x+1,y);			// 0 1
		blocks[2].setLocation (x+1,y+1);		//   2
		blocks[3].setLocation (x+1,y+2); break;	//   3
	case Left:
		blocks[1].setLocation (x-2,y+1);			//     0
		blocks[2].setLocation (x-1,y+1);			// 1 2 3
		blocks[3].setLocation (x,y+1); break;
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_L::rotate ()
{
	switch ( status )
	{
	case Head:
		blocks[0].moveDown();
		blocks[1].moveRight();
		blocks[2].moveUp(); blocks[2].moveRight(); blocks[2].moveRight();
		blocks[3].moveLeft();
		break;
	case Right:
		blocks[2].moveLeft(); blocks[2].moveDown();
		blocks[3].moveRight(); blocks[3].moveDown();
		break;
	case Tail:
		blocks[0].moveRight();
		blocks[1].moveDown(); blocks[1].moveLeft(); blocks[1].moveLeft();
		blocks[2].moveLeft();
		blocks[3].moveUp();
		break;
	case Left:
		blocks[0].moveLeft(); blocks[0].moveUp();
		blocks[1].moveRight(); blocks[1].moveUp();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
Brick_J::Brick_J (int x, int y)
{
	blocks[0].setLocation (x,y);

	switch ( status )
	{
	case Head:
		blocks[1].setLocation (x,y+1);			//   0
		blocks[2].setLocation (x-1,y+2);			//   1
		blocks[3].setLocation (x,y+2); break;	// 2 3
	case Right:
		blocks[1].setLocation (x,y+1);			// 0
		blocks[2].setLocation (x+1,y+1);		// 1 2 3
		blocks[3].setLocation (x+2,y+1); break;
	case Tail:
		blocks[1].setLocation (x+1,y);			// 0 1
		blocks[2].setLocation (x,y+1);			// 2
		blocks[3].setLocation (x,y+2); break;	// 3
	case Left:
		blocks[1].setLocation (x+1,y);			// 0 1 2
		blocks[2].setLocation (x+2,y);			//     3
		blocks[3].setLocation (x+2,y+1); break;
	default: std::cerr << "Unidentifiable Constuctor Error.:(\n"; exit(-1); break;
	}
}
void Brick_J::rotate ()
{
	switch ( status )
	{
	case Head:
		blocks[0].moveDown(); blocks[0].moveLeft();
		blocks[1].moveDown(); blocks[1].moveLeft();
		blocks[2].moveRight();
		blocks[3].moveRight();
		break;
	case Right:
		blocks[1].moveUp(); blocks[1].moveRight();
		blocks[2].moveLeft();
		blocks[3].moveLeft(); blocks[3].moveLeft(); blocks[3].moveDown();
		break;
	case Tail:
		blocks[0].moveLeft();
		blocks[1].moveLeft();
		blocks[2].moveUp(); blocks[2].moveRight();
		blocks[3].moveUp(); blocks[3].moveRight();
		break;
	case Left:
		blocks[0].moveRight(); blocks[0].moveRight(); blocks[0].moveUp();
		blocks[1].moveRight();
		blocks[2].moveDown(); blocks[2].moveLeft();
		break;
	default: std::cerr << "Unidentifiable Rotation Error.:(\n"; exit(-1); break;
	}
	status = (Status)((status+1) % 4);
}
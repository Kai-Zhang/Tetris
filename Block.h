#ifndef BLOCK_H_
#define BLOCK_H_

class Block
{
	// Block Coordinate
	int x;
	int y;
	// Coordinate Starts From 1
public:
	Block (int xx=1, int yy=1): x(xx), y(yy) { }
	virtual ~Block () { }

	// R/W Coordinate
	void setLocation (int xx, int yy) { x = xx; y = yy; }
	int getX () const { return x; }
	int getY () const { return y; }

	// Block Movement
	void moveDown () { ++ y; }
	void moveUp () { -- y; }
	void moveLeft () { -- x; }
	void moveRight () { ++ x; }

};

#endif
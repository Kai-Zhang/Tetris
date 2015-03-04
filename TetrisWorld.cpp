#include "Bricks.h"
#include "TetrisWorld.h"
#include <cstring>
#include <Windows.h>
#include <cstdio>

TetrisWorld::TetrisWorld (int alignSize, int verticalSize): aSize(alignSize), vSize(verticalSize)
{
	// Build the Screen Matrix
	// Frame Included. Element Exists From 1 to aSize/vSize
	screen = new char* [vSize+2];
	for ( int row=0; row < vSize+2; ++row )
	{
		screen[row] = new char [aSize+2];
		// Optional
		memset (screen[row],0,sizeof(char)*(aSize+2));
	}
	for ( int col=0; col <= aSize+1; ++col )
		screen[0][col] = screen[vSize+1][col] = '-';
	for ( int row=1; row <= vSize; ++row )
	{
		screen[row][0] = '|';
		// Necessary
		memset(screen[row]+1,' ',sizeof(char)*aSize);
		screen[row][aSize+1] = '|';
	}
}
TetrisWorld::~TetrisWorld ()
{
	// Delete Every Row
	for ( int row=0; row <= vSize+1; ++row )
		delete [] screen[row];
	delete [] screen;
}
void clearScreen(HANDLE hConsole) 
{
	#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);} 

	COORD coordScreen = { 0, 0 }; // Here's the Cursor's Home
	BOOL bSuccess; 
	DWORD cCharsWritten; 
	CONSOLE_SCREEN_BUFFER_INFO csbi; // To Get Buffer Info
	DWORD dwConSize; // Number of Character Cells in the Current Buffer

	// Get the Number of Character Cells in the Current Buffer

	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi ); 
	PERR( bSuccess, "GetConsoleScreenBufferInfo" ); 
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 

	// Fill the Entire Screen With Blanks

	bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', 
	dwConSize, coordScreen, &cCharsWritten ); 
	PERR( bSuccess, "FillConsoleOutputCharacter" ); 

	// Get the Current Text Attribute

	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi ); 
	PERR( bSuccess, "ConsoleScreenBufferInfo" ); 

	// Set the Buffer's Attributes Accordingly

	bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes, 
	dwConSize, coordScreen, &cCharsWritten ); 
	PERR( bSuccess, "FillConsoleOutputAttribute" ); 

	// Put the Cursor at (0, 0)

	bSuccess = SetConsoleCursorPosition( hConsole, coordScreen ); 
	PERR( bSuccess, "SetConsoleCursorPosition" ); 
	return; 
}
void TetrisWorld::clear () const
{
	// Direct Access to Buffer to Speed Up
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	clearScreen (hStdOut);
}
void TetrisWorld::print (Brick* cur, Brick* next, int score) const
{
	// Build Auxiliary Array to Store the Next Brick
	int coordX[4] = {0};
	int coordY[4] = {0};
	// Get Relative Coordinate
	for ( int i = 0; i < 4; ++i )
	{
		coordX[i] = next->blocks[i].getX() - next->blocks[0].getX();
		coordY[i] = next->blocks[i].getY() - next->blocks[0].getY();
	}
	// Adjust to Positive Number ( to Print Space )
	for ( int i = 0; i < 4; ++i )
		if ( coordX[i] < 0 )
		{
			int temp = -coordX[i];
			for ( int j = 0; j < 4; ++j )
				coordX[j] += temp;
		}
	
	// Main Printer
	for ( int row = 0; row <= vSize+1; ++row )
	{
		putchar (' ');
		for ( int col = 0; col <= aSize+1; ++col )
		{
			bool flag = false;
			// Print the Current Brick
			for ( int i=0; i < 4; ++i )
				if ( cur != NULL && cur->blocks[i].getX() == col && cur->blocks[i].getY() == row )
				{
					// Use '*' Instead of ¡ö ( Store/Print with ASCII Code )
					putchar ('*');
					flag = true;
					break;
				}
			if ( !flag )
				putchar (screen[row][col]);
		}
		// Print Right Column
		printf ("   ");
		if ( row == 1 )
			printf ("Score:");
		else if ( row == 2 )
			printf ("%d",score);
		else if ( row == vSize-3 )
			printf ("Press R to restart.");
		else if ( row == vSize-1 )
			printf ("Press Q to leave at anytime.");
		else if ( row == vSize/2-2 )
			printf ("Next Brick:");
		else if ( row >= vSize/2 && row <= vSize/2+3 )
			for ( int blockPtr = 0; blockPtr < 4; ++blockPtr )
				if ( coordY[blockPtr] == row-vSize/2 )
				{
					// First Block or Different Row
					if ( blockPtr == 0 || coordY[blockPtr-1] != coordY[blockPtr] )
						// Print Space to Align
						for ( int blank = 0; blank < coordX[blockPtr]; ++ blank )
							putchar (' ');
					putchar ('*');
				}
		putchar ('\n');
	}
}
void TetrisWorld::reset ()
{
	// Delete Current Data
	this->~TetrisWorld ();
	// Constructor
	screen = new char* [vSize+2];
	for ( int row=0; row < vSize+2; ++row )
	{
		screen[row] = new char [aSize+2];
		memset (screen[row],0,sizeof(char)*(aSize+2));
	}
	for ( int col=0; col <= aSize+1; ++col )
		screen[0][col] = screen[vSize+1][col] = '-';
	for ( int row=1; row <= vSize; ++row )
	{
		screen[row][0] = '|';
		memset(screen[row]+1,' ',sizeof(char)*aSize);
		screen[row][aSize+1] = '|';
	}
}

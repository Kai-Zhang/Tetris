#include <iostream>
#include <Windows.h>
#include "GameControl.h"

void clearScreen(HANDLE);
bool isContinue ()
{
	char choice = 'Y';
	// Clear Screen
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	clearScreen (hStdOut);
	// Get Choice
	std::cout << "\n\n\n          Game Over.\n\n\n" << std::endl
		<< "    Again? (Y/y for Yes, others for No)" << std::endl
		<< "    > ";
	std::cin >> choice;
	// Judge And Return
	if ( choice == 'Y' || choice == 'y' )
		return true;
	return false;
}

int main ()
{
	// Build A Controller
	GameControl game;
	
	game.run ();
	// Play Again
	while ( isContinue () )
	{
		game.reset ();
		game.run ();
	}
	// Say Goodbye
	std::cout << "\n\n\n          GoodBye!\n\n\n";
	system("pause");
	return 0;
}
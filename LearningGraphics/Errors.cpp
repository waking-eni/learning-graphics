#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>

// prints out an error message and exits the game
void fatal_error(std::string error_string)
{
	std::cout << error_string << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}
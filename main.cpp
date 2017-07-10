#include <iostream>
#include "SDL.h"
#undef main


using std::cout;
using std::endl;

int main(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		cout << "I test something" << endl;

	getchar();
	return 0;
}

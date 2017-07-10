#include <iostream>
#include <SDL2/SDL.h>
#undef main // Visual Studio

using std::cout;
using std::endl;

int main(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		cout << "Hello World!" << endl;

	SDL_Delay(3000);
	return 0;
}

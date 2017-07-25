#ifdef __linux__ // Linux
#include <SDL2/SDL.h> //  SDL library
#include <SDL2/SDL_image.h>
#include <iostream>
#endif

#ifdef _WIN32 || _WIN64 // Windows
#include "SDL.h" //  SDL library
#include "SDL_image.h" // SDL Image
#include <iostream>
#endif

#include "Collision.hpp"

// Initialise la hitbox
void Collision::collisionInit(SDL_Rect* rectBox)
{
	a = rectBox;
}

// Test si il y a une collision entre 2 objets
bool Collision::collisionTest(Collision rectCollider)
{
	SDL_Rect* b = rectCollider.a;

	if (a->y >= b->y + b->h)
		return 0;
	if (a->x >= b->x + b->w)
		return 0;
	if (a->y + a->h <= b->y)
		return 0;
	if (a->x + a->w <= b->x)
		return 0;
	return 1;
}
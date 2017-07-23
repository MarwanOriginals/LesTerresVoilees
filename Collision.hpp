#ifndef COLLISION_HPP
#define COLLISION_HPP

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

class Collision
{
public:
	
	SDL_Rect* a = NULL;

	void collisionInit(SDL_Rect* rectBox);

	bool collisionTest(Collision rectCollider);

private:

};


#endif
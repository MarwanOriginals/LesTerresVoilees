#ifndef PNJ_HPP
#define PNJ_HPP

#ifdef __linux__ // Linux
#include <SDL2/SDL.h> //  SDL library
#include <SDL2/SDL_image.h>
#include <iostream>
#endif

#ifdef _WIN32 || _WIN64 // Windows
#include "SDL.h" //  SDL library
#include "SDL_image.h" // SDL Image
#include <iostream>
#include "Texture.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#endif

class Pnj
{
public:

	enum DIRECTION
	{
		HAUT,
		BAS,
		GAUCHE,
		DROITE,
		IDLE,
	};

	std::string nom;
	Texture sprite;
	int attenteMax = 180;
	int attente = 0;
	int pixelDeplacementMax = 40;
	int pixelDeplacement = 0;
	int rdmDirection;
	bool pnjIsWalk = 0;

	// Test annimation
	int maxFrame = 9;
	int currentFrame = 0;
	int delayMax = 1;
	int delay = 0;

	Pnj(std::string n, std::string fileName, SDL_Renderer * pRenderer);
	void Deplacement(SDL_Renderer * pRenderer);
	void Animation(SDL_Renderer * pRenderer);

private:

};

#endif
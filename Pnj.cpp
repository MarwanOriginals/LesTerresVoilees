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

#include "Pnj.hpp"




Pnj::Pnj(std::string n, std::string fileName, SDL_Renderer * pRenderer)
{
	srand(time(NULL));
	nom = n;
	sprite.load(fileName, pRenderer);


}


void Pnj::Deplacement(SDL_Renderer * pRenderer)
{
	if (attente != attenteMax)
	{
		attente++;
	}
	else
	{
		if (rdmDirection == HAUT && attente != 0)
		{
			if(pixelDeplacement!=pixelDeplacementMax)
			{
				sprite.a.y = 0;
				pnjIsWalk = 1;
				sprite.b.y -= 1;
				pixelDeplacement++;
			}
			else
			{
				pnjIsWalk = 0;
				attente = 0;
				pixelDeplacement = 0;
				rdmDirection = rand() % 5 + 0;
			}
		}

		if (rdmDirection == BAS && attente != 0)
		{
			if (pixelDeplacement != pixelDeplacementMax)
			{
				sprite.a.y = 64 * 2;
				pnjIsWalk = 1;
				sprite.b.y += 1;
				pixelDeplacement++;
			}
			else
			{
				pnjIsWalk = 0;
				attente = 0;
				pixelDeplacement = 0;
				rdmDirection = rand() % 5 + 0;
			}
		}

		if (rdmDirection == GAUCHE && attente != 0)
		{
			if (pixelDeplacement != pixelDeplacementMax)
			{
				sprite.a.y = 64;
				pnjIsWalk = 1;
				sprite.b.x -= 1;
				pixelDeplacement++;
			}
			else
			{
				pnjIsWalk = 0;
				attente = 0;
				pixelDeplacement = 0;
				rdmDirection = rand() % 5 + 0;
			}
		}

		if (rdmDirection == DROITE && attente != 0)
		{
			if (pixelDeplacement != pixelDeplacementMax)
			{
				sprite.a.y = 64 * 3;
				pnjIsWalk = 1;
				sprite.b.x += 1;
				pixelDeplacement++;
			}
			else
			{
				pnjIsWalk = 0;
				attente = 0;
				pixelDeplacement = 0;
				rdmDirection = rand() % 5 + 0;
			}
		}
		
		if (rdmDirection == IDLE && attente != 0)
		{
			if (pixelDeplacement != pixelDeplacementMax)
			{
				pixelDeplacement++;
			}
			else
			{
				attente = 0;
				pixelDeplacement = 0;
				rdmDirection = rand() % 5 + 0;
			}
		}
	}
}

void Pnj::Animation(SDL_Renderer * pRenderer)
{
	if (pnjIsWalk)
	{
		if (delay == delayMax)
		{
			currentFrame++;
			if (currentFrame == maxFrame)
			{
				currentFrame = 0;
			}
			sprite.a.x = currentFrame * 64;
			delay = 0;
		}
		else
			delay++;
	}
	else
		sprite.a.x = 0;
}

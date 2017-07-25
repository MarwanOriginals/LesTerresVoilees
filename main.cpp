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

#include <iostream>   //  Standard IO librar
#include "Texture.hpp" // Implantation texture
#include "Collision.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

using std::cout;
using std::endl;


int main(int argc, char* args[])
{

	

	// Enumération des touches [ DEFAULT = 0, HAUT = 1 ... TOTAL = 5]
	enum Touche
	{
		DEFAULT,
		HAUT,
		BAS,
		GAUCHE,
		DROITE,
		TOTAL
	};

    //  The SDL_Window object is used to create a window
    SDL_Window* window = nullptr;

    //  The SDL_Surface object is the "blackboard" of our window
    SDL_Surface* screen_surface = nullptr;

	// Boucle qui tourne pour chaque event
	bool boucle = true;

	// Initialisation d'un évenement "e" 
	SDL_Event e;

	// Creation texture test
	Texture background, mage;

	// Renderer
	SDL_Renderer* renderer;

	// Collision
	Collision joueur, limitCollision[4];

	// Rect
	SDL_Rect limit[4];

	// Test annimation sprite 
	int maxFrame = 9;
	int currentFrame = 0;
	const int delayMax = 1;
	int delay = 0;
	bool isWalk = 0;

	// Init Everything
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Error when initializing SDL, SDL Error : " << SDL_GetError() << endl;
	}
	else
	{
		//  Create window
		window = SDL_CreateWindow("Les Terres Voilées", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			cout << "Error on creating window, SDL Error : " << SDL_GetError() << endl;
		}
		else
		{
			//Create Renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == nullptr)
			{
				cout << "Error on creating renderer, SDL Error : " << SDL_GetError() << endl;;
			}
			else
			{
				// Initialize  renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//  Initialize PNG loading
				int img_flag = IMG_INIT_PNG;

				if (!(IMG_Init(img_flag) & img_flag))
				{
					cout << "Error on creating SDL image, SDL_image Error : " << IMG_GetError() << endl;
				}
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 100, 90, 200, 100);

	background.load("background.png", renderer);
	background.draw(0, 0, 1280, 720, renderer);

	mage.load("mageWalk.png", renderer);
	mage.draw(0, 128, 350, 500, 63, 63, renderer);
	joueur.collisionInit(&mage.b);

	// Init des limites
	// Gauche
	limit[0].x = 0 - 1;
	limit[0].y = 0 - 1;
	limit[0].h = SCREEN_HEIGHT - 1;
	limit[0].w = 0;
	limitCollision[0].collisionInit(&limit[0]);

	// Haut
	limit[1].x = 0 - 5;
	limit[1].y = 0 - 5;
	limit[1].h = 0;
	limit[1].w = SCREEN_WIDTH - 5;
	limitCollision[1].collisionInit(&limit[1]);

	// Droite
	limit[2].x = SCREEN_WIDTH + 2;
	limit[2].y = 0 + 2;
	limit[2].h = SCREEN_HEIGHT + 2;
	limit[2].w = 0;
	limitCollision[2].collisionInit(&limit[2]);

	// Bas
	limit[3].x = 0 + 5;
	limit[3].y = SCREEN_HEIGHT + 5;
	limit[3].h = 0;
	limit[3].w = SCREEN_WIDTH + 5;
	limitCollision[3].collisionInit(&limit[3]);




	while (boucle)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				boucle = false;
			}
		}

		const Uint8* key = SDL_GetKeyboardState(NULL);

		if (key[SDL_SCANCODE_RIGHT])
		{
			isWalk = 1;
			mage.a.y = 64*3;
			mage.b.x += 7;

			for (int i = 0; i < 4; i++)
			{
				if (joueur.collisionTest(limitCollision[i]))
				{
					mage.b.x -= 7;
					isWalk = 0;
				}
			}
		}

		if (key[SDL_SCANCODE_LEFT])
		{
			isWalk = 1;
			mage.a.y = 64;
			mage.b.x -= 7;

			for (int i = 0; i < 4; i++)
			{
				if (joueur.collisionTest(limitCollision[i]))
				{
					mage.b.x += 7;
					isWalk = 0;
				}
			}
		}

		if (key[SDL_SCANCODE_DOWN])
		{
			isWalk = 1;
			mage.a.y = 64 * 2;
			mage.b.y += 7;

			for (int i = 0; i < 4; i++)
			{
				if (joueur.collisionTest(limitCollision[i]))
				{
					mage.b.y -= 7;
					isWalk = 0;
					if (key[SDL_SCANCODE_LEFT])
						isWalk = 1;
					if (key[SDL_SCANCODE_RIGHT])
						isWalk = 1;
				}
			}
		}
		if (key[SDL_SCANCODE_UP])
		{
			isWalk = 1;
			mage.a.y = 0;
			mage.b.y -= 7;

			for (int i = 0; i < 4; i++)
			{
				if (joueur.collisionTest(limitCollision[i]))
				{
					mage.b.y += 7;
					isWalk = 0;
					if(key[SDL_SCANCODE_LEFT])
						isWalk = 1;
					if(key[SDL_SCANCODE_RIGHT])
						isWalk = 1;
				}
			}
		}

		background.update(renderer);

		// Animation du personnage
		if (isWalk && !(key[SDL_SCANCODE_LEFT] && key[SDL_SCANCODE_RIGHT]) && !(key[SDL_SCANCODE_DOWN] && key[SDL_SCANCODE_UP]))
		{
			if (delay == delayMax)
			{
				currentFrame++;
				if (currentFrame == maxFrame)
				{
					currentFrame = 0;
				}
				mage.a.x = currentFrame * 64;
				delay = 0;
			}
			else
				delay++;
		}
		else
			mage.a.x = 0;

		mage.update(renderer);
		isWalk = 0;

		//Update screen
		SDL_RenderPresent(renderer);
	}

	//  Updating surface
	SDL_UpdateWindowSurface(window);

    //  Destroy window
    SDL_DestroyWindow(window);

    //  End SDL subsystems
    SDL_Quit();

    return 0;
}


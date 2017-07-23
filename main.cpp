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
	Texture test, background;

	// Renderer
	SDL_Renderer* renderer;

	// Collision
	Collision joueur, rectangle;


    //  Initialisation
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error when initializing SDL, SDL Error : " << SDL_GetError() << endl;
    }
    else
    {
        //  Create window
        window = SDL_CreateWindow("Les Terres Voilées", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if(window == nullptr)
        {
            cout << "Error on creating window, SDL Error : " << SDL_GetError() << endl;
        }

        else
        {
            //  Get window surface
            screen_surface = SDL_GetWindowSurface(window);

            //  Fill the sufrace white
            SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

            //  Updating surface
            SDL_UpdateWindowSurface(window);
        }			
			
    }

	// Initialisation du renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 100, 90, 200, 100);

	test.load("sprite.png", renderer);
	background.load("background.png", renderer);

	background.draw(0, 0, 1280, 720, renderer);
	test.draw(200, 200, 133, 196, renderer);

	// Initialisation collision
	SDL_Rect mur;

	mur.x = 900;
	mur.y = 250;
	mur.h = 300;
	mur.w = 300;

	joueur.collisionInit(&test.b);
	rectangle.collisionInit(&mur);


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
			SDL_DestroyTexture(test.m_texture);
			test.load("spriteGR.png", renderer);
			test.b.x += 7;

			if (joueur.collisionTest(rectangle))
				test.b.x -= 7;
		}

		if (key[SDL_SCANCODE_LEFT])
		{
			SDL_DestroyTexture(test.m_texture);
			test.load("sprite.png", renderer);
			test.b.x -= 7;

			if (joueur.collisionTest(rectangle))
				test.b.x += 7;
		}

		if (key[SDL_SCANCODE_DOWN])
		{
			test.b.y += 7;

			if (joueur.collisionTest(rectangle))
				test.b.y -= 7;
		}
		if (key[SDL_SCANCODE_UP])
		{
			test.b.y -= 7;

			if (joueur.collisionTest(rectangle))
				test.b.y += 7;
		}

		background.update(renderer);
		SDL_RenderFillRect(renderer, &test.b);
		test.update(renderer);
		SDL_RenderFillRect(renderer, &mur);

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


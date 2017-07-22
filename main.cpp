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
	Texture test;

	// Renderer
	SDL_Renderer* renderer;

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
	test.draw(200, 200, 133, 196, renderer);

	

	while (boucle)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				boucle = false;
			}

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					test.b.y -= 10;
					break;

				case SDLK_DOWN:
					test.b.y += 10;
					break;

				case SDLK_LEFT:
					SDL_DestroyTexture(test.m_texture);
					test.load("sprite.png", renderer);
					test.b.x -= 10;
					break;

				case SDLK_RIGHT:
					SDL_DestroyTexture(test.m_texture);
					test.load("spriteGR.png", renderer);
					test.b.x += 10;
					break;

				default:
					break;
				}
			}
		}
		
		test.update(renderer);

	}

	//  Updating surface
	SDL_UpdateWindowSurface(window);

    //  Destroy window
    SDL_DestroyWindow(window);

    //  End SDL subsystems
    SDL_Quit();

    return 0;
}


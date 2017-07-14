#ifdef __linux__ // Linux
#include <SDL2/SDL.h> //  SDL library
#include <SDL2/SDL_image.h>
#endif

#ifdef _WIN32 || _WIN64 // Windows
#include "SDL.h" //  SDL library
#include "SDL_image.h" // SDL Image
#endif

#include <iostream>   //  Standard IO librar

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

using std::cout;
using std::endl;

// En attendant la classe texture
SDL_Surface* chargementSurface(std:: string chemin)
{
	SDL_Surface* surface = IMG_Load(chemin.c_str());
	return surface;
}

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

	// Initialisation des images
	SDL_Surface *firstImage = nullptr, *sprite = nullptr, *touchePresse[TOTAL];

	// Initialisation de la position de l'image
	SDL_Rect positionFirstImage,positionSprite;

	// Boucle qui tourne pour chaque event
	bool boucle = true;

	// Initialisation d'un évenement "e" 
	SDL_Event e;

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

			// Chargement de l'image bitmap
			firstImage = SDL_LoadBMP("firstImage.bmp");

			// Si l'image a une erreur
			if (firstImage == NULL)
			{
				cout << "Error Image SDL" << SDL_GetError() << endl;
			}

			// Chargement image png
			sprite = IMG_Load("sprite.png");

			// Optimisation de l'image (à voir pour les grosses images)
			sprite = SDL_ConvertSurfaceFormat(sprite, SDL_PIXELFORMAT_RGBA8888,0);

			// Si l'image a une erreur
			if (sprite == NULL)
			{
				cout << "Error Image SDL" << SDL_GetError() << endl;
			}


			// Position x et y des images
			positionFirstImage.x = SCREEN_WIDTH / 4;
			positionFirstImage.y = SCREEN_HEIGHT / 4;
			
			positionSprite.x = 0;
			positionSprite.y = 0;

			// Blitage de la surface
			SDL_BlitSurface(firstImage, NULL, screen_surface, &positionFirstImage);
			SDL_BlitSurface(sprite, NULL, screen_surface, &positionSprite);

			//  Updating surface
			SDL_UpdateWindowSurface(window);

    }

	// Chargement des textures de déplacement
	touchePresse[DEFAULT] = chargementSurface("sprite.png");
	touchePresse[HAUT] = chargementSurface("sprite.png");
	touchePresse[BAS] = chargementSurface("sprite.png");
	touchePresse[GAUCHE] = chargementSurface("sprite.png");
	touchePresse[DROITE] = chargementSurface("spriteGR.png");


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
					positionSprite.y-=10;
					break;

				case SDLK_DOWN:
					positionSprite.y+=10;
					break;

				case SDLK_LEFT:
					sprite = touchePresse[GAUCHE];
					positionSprite.x-=10;
					break;

				case SDLK_RIGHT:
					sprite = touchePresse[DROITE];
					positionSprite.x+=10;
					break;

				default:
					sprite = touchePresse[DEFAULT];
					break;
				}
			}
		}

		//  Fill the sufrace white
		SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

		// Blitage de la surface
		SDL_BlitSurface(firstImage, NULL, screen_surface, &positionFirstImage);
		SDL_BlitSurface(sprite, NULL, screen_surface, &positionSprite);

		//  Updating surface
		SDL_UpdateWindowSurface(window);

	}

	// Destroy Image
	SDL_FreeSurface(firstImage);
	SDL_FreeSurface(sprite);

    //  Destroy window
    SDL_DestroyWindow(window);

    //  End SDL subsystems
    SDL_Quit();

    return 0;
}


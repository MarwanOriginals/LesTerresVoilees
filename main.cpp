#ifdef __linux__ // Linux
#include <SDL2/SDL.h> //  SDL library
// à completer avec la SDL image
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

int main(int argc, char* args[])
{
    //  The SDL_Window object is used to create a window
    SDL_Window* window = nullptr;

    //  The SDL_Surface object is the "blackboard" of our window
    SDL_Surface* screen_surface = nullptr;

	// Initialisation des images
	SDL_Surface *firstImage = nullptr, *sprite = nullptr;

	// Initialisation de la position de l'image
	SDL_Rect positionFirstImage;

    //  Initialisation
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error when initializing SDL, SDL Error : " << SDL_GetError() << endl;
    }
    else
    {
        //  Create window

        window = SDL_CreateWindow("Les Terres Voilées", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

			// Si l'image a une erreur
			if (sprite == NULL)
			{
				cout << "Error Image SDL" << SDL_GetError() << endl;
			}


			// Position x et y des images
			positionFirstImage.x = SCREEN_WIDTH / 4;
			positionFirstImage.y = SCREEN_HEIGHT / 4;

			// Blitage de la surface
			SDL_BlitSurface(firstImage, NULL, screen_surface, &positionFirstImage);
			SDL_BlitSurface(sprite, NULL, screen_surface, NULL);

			//  Updating surface
			SDL_UpdateWindowSurface(window);

            // Wait five seconds
            SDL_Delay(5000);


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

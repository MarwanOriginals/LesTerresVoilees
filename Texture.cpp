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

#include "Texture.hpp"

bool Texture::load(std::string fileName, SDL_Renderer* pRenderer)
{
		
	// Opening a image file
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	// If there is an error
    if(pTempSurface == 0)
    {
        return false;
    }

	// Create a texture
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	// Destroy surface
    SDL_FreeSurface(pTempSurface);

	// When the texture created was loaded sucessfully
    if(pTexture != nullptr)
    {
        m_texture = pTexture;
        return true;
    }

    return false;
}

void Texture::draw(int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_RenderClear(pRenderer);

    a.x = 0;
    a.y = 0;

    a.w = b.w = width;
    a.h = b.h = height;

    b.x = x;
    b.y = y;

	//Render texture to screen
	SDL_RenderCopy(pRenderer, m_texture, &a, &b);

	//Update screen
	SDL_RenderPresent(pRenderer);
}

void Texture::update(SDL_Renderer* pRenderer)
{

	//Render texture to screen
	SDL_RenderCopy(pRenderer, m_texture, &a, &b);

}

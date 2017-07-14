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
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if(pTempSurface == 0)
    {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if(pTexture != nullptr)
    {
        m_texture = pTexture;
        return true;
    }

    return false;
}

void Texture::draw(int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;

    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &destRect, 0, 0, flip);
}

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

class Texture
{
public:
    bool load(std::string fileName, SDL_Renderer* pRenderer);

    void draw(int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    SDL_Texture* m_texture;
};

#endif

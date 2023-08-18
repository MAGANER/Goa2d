#include"Texture.h"
using namespace Goat2d::core;

Texture::Texture(const std::string& path, SDL_Renderer* renderer)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        ok = false;
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            ok = false;
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        this->renderer = renderer;
    }
}

void Texture::draw()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}
Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}
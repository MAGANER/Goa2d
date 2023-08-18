#include"Image.h"
using namespace Goat2d::core;


Image::Image(const std::string& path, SDL_Surface* screen_surface)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        auto error = "Unable to load image " + path + " SDL_image Error:";
        print_error(error);
        write_error(error);
    }
    else
    {
        img_surface = SDL_ConvertSurface(surface, screen_surface->format, 0);
        if (img_surface == NULL)
        {
            auto error = "Unable to optimize image " + path + " SDL Error:";
            print_error(error);
            write_error(error);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(surface);
        ok = true;
    }
}
Image::~Image()
{
    SDL_FreeSurface(img_surface);
}
void Image::blit(SDL_Surface* screen_surface, SDL_Rect* stretchRect)
{
    SDL_BlitScaled(img_surface, NULL, screen_surface, stretchRect);
}
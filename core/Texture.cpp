#include"Texture.h"
#ifdef USE_SDL_IMG
using namespace Goat2d::core;

Texture::Texture(const std::string& path, 
                 SDL_Renderer* renderer,
                 float rotation_angle,
                 FlipType flipping_type):
    ChangableObject(renderer,rotation_angle,flipping_type)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        ok = false;
        print_error("Unable to load image! SDL_image Error: ");
        write_error("Unable to load image! SDL_image Error: ");
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            ok = false;
            print_error("Unable to load image! SDL_image Error: ");
            write_error("Unable to load image! SDL_image Error: ");
        }

        SDL_Point size;
        SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
        this->size.x = size.x;
        this->size.y = size.y;

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        this->renderer = renderer;


        drawing_rect = new SDL_Rect;
        drawing_rect->x = 0;
        drawing_rect->y = 0;
        drawing_rect->w = this->size.x;
        drawing_rect->h = this->size.y;
    }
}
void Texture::draw()
{
    if (!visible)
        return;

	SDL_RenderCopy(renderer, texture, NULL, drawing_rect);
}
void Texture::draw(const Vector2f& pos)
{
    if (!visible)
        return;

    SDL_Rect r;
    r.x = pos.x;
    r.y = pos.y;
    r.w = drawing_rect->w;
    r.h = drawing_rect->h;
    SDL_RenderCopy(renderer, texture, NULL, &r);
}
Texture::~Texture()
{
    if (drawing_rect != nullptr)
        delete drawing_rect;

	SDL_DestroyTexture(texture);
}
#endif
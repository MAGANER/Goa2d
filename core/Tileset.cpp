#include"Tileset.h"
#ifdef USE_SDL_IMG
using namespace Goat2d::core;

Tileset::Tileset(const std::string& path, const Vector2i& tile_size, SDL_Renderer* renderer)
	:renderer(renderer)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        ok = false;
        print_error("Unable to load image! SDL_image Error:");
        write_error("Unable to load image! SDL_image Error:");
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            ok = false;
            print_error("Unable to load image! SDL_image Error:");
            write_error("Unable to load image! SDL_image Error:");
        }

        //it should be splittable
        SDL_Point size;
        SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
        if ((size.x % tile_size.x) != 0 or
            (size.y % tile_size.y) != 0)
        {
            ok = false;
            print_error("Unable to split tileset with provided sizes: x = "+std::to_string(size.x)+", y = "+std::to_string(size.y));
            write_error("Unable to split tileset with provided sizes: x = " + std::to_string(size.x) + ", y = " + std::to_string(size.y));
        }
        else
        {
            split_tiles(size, tile_size);
        }


        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        this->renderer = renderer;
    }
}
Tileset::~Tileset()
{
    SDL_DestroyTexture(texture);

    if (drawing_rect == nullptr)
        delete drawing_rect;
}
void Tileset::split_tiles(const SDL_Point& size, const Vector2i& tile_size)
{
    auto height = (int)(size.y / tile_size.y);
    auto width = (int)(size.x / tile_size.x);

    Vector2i curr_pos(0,0);
    for (size_t y = 0;y<height;++y)
    {
        for (size_t x = 0;x<width;++x)
        {
            tiles.push_back(SDL_Rect{ .x = curr_pos.x,.y = curr_pos.y,.w = tile_size.x,.h = tile_size.y });
            curr_pos.x = curr_pos.x + tile_size.x;
        }
        curr_pos.x = 0;
        curr_pos.y = curr_pos.y + tile_size.y;
    }
}
bool Tileset::draw(size_t tile_code, const Vector2i& pos)
{
    if (tile_code > tiles.size())
    {
        print_error("unable to draw tile with code:" + std::to_string(tile_code));
        write_error("unable to draw tile with code:" + std::to_string(tile_code));
        return false;
    }

    auto tile = tiles[tile_code];
    SDL_Rect render_quad = { .x = pos.x, .y = pos.y, .w = tile.w,.h = tile.h };
    SDL_RenderCopy(renderer, texture, &tile, &render_quad);

    return true;
}
bool Tileset::draw(size_t tile_code, const Vector2f& pos)
{
    if (tile_code > tiles.size())
    {
        print_error("unable to draw tile with code:" + std::to_string(tile_code));
        write_error("unable to draw tile with code:" + std::to_string(tile_code));
        return false;
    }

    auto tile = tiles[tile_code];
    SDL_FRect render_quad = { .x = pos.x, .y = pos.y, .w = (float)tile.w,.h = (float)tile.h };
    SDL_RenderCopyF(renderer, texture, &tile, &render_quad);

    return true;
}
#endif
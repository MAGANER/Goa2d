#ifndef IMAGE_H
#define IMAGE_H
#include"SDL_image.h"
#include"ErrorLogger.h"
namespace Goat2d
{
namespace core 
{
	class Image
	{
		SDL_Surface* img_surface = nullptr;
		bool ok = false;
	public:
		Image(const std::string& path, SDL_Surface* screen_surface);
		~Image();

		void blit(SDL_Surface* screen_surface, SDL_Rect* stretchRect);
		bool is_ok()const { return ok; }
	};

	static inline SDL_Rect make_rect(int x, int y, int width, int height)
	{
		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.w = width;
		r.h = height;
		return r;
	}
};
};

#endif
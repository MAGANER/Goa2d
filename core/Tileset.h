#include"core/Definitors.hpp"
#ifdef USE_SDL_IMG


#ifndef TILESET_H
#define TILESET_H
#include<tuple>
#include<string>
#include<vector>

#include"Vector.h"
#include"core/ErrorLogger.h"
#include"SDL_image.h"

namespace Goat2d
{
namespace core
{
	class Tileset
	{
		//! pixel data
		SDL_Texture* texture = nullptr;

		//! size, pos
		SDL_Rect* drawing_rect = nullptr;

		//! if it's true, than everything loaded correctly
		bool ok = true;

		//! tile rects
		std::vector<SDL_Rect> tiles;
	protected:

		//! Can not be changed, pointer to Window's render
		SDL_Renderer* renderer = nullptr; //use it to draw
	public:
		Tileset(const std::string& path, const Vector2i& tile_size,SDL_Renderer* renderer);
		~Tileset();

		//! draw specific part of tilest and return true if it's ok, unless return false
		bool draw(size_t tile_code, const Vector2i& pos);

		bool is_ok()const { return ok; }
	private:

		//! compute rectangles with tiles
		void split_tiles(const SDL_Point& texture_size,const Vector2i& tile_size);
	};
};
};
#endif //TILESET_H
#endif //USE_SDL_IMG
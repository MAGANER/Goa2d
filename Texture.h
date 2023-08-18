#ifndef TEXTURE_H
#define TEXTURE_H
#include"DrawableObject.h"
#include"ErrorLogger.h"
namespace Goat2d
{
namespace core 
{
	class Texture: public DrawableObject
	{
		SDL_Texture* texture = nullptr;
		bool ok = true;

		SDL_Renderer* renderer = nullptr; //use it to draw

		Vector2i size;
		SDL_Rect* drawing_rect = nullptr;
	public:
		Texture(const std::string& path,SDL_Renderer* renderer);
		~Texture();

		void draw(const Vector2i& position);
		bool is_ok()const { return ok; }

		Vector2i const& get_size()const { return size; }
		Vector2i const& get_pos()const { return Vector2i(drawing_rect->x, drawing_rect->y); }
	};
	

};
};
#endif
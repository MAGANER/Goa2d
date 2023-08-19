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

		void update_pos(const Vector2i& new_pos)
		{
			pos = new_pos;

			drawing_rect->x = new_pos.x;
			drawing_rect->y = new_pos.y;
		}
	};
	

};
};
#endif
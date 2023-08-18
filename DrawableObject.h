#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H
#include"SDL_image.h"
#include"Vector.h"
namespace Goat2d
{
namespace core
{
	class DrawableObject
	{
		SDL_Renderer* renderer = nullptr; //use it to draw

	protected:
		DrawableObject(SDL_Renderer* renderer):renderer(renderer){}
		~DrawableObject(){}
	public:
		virtual void draw(const Vector2i& position) = 0;

		virtual Vector2i const& get_size()const =0;
		virtual Vector2i const& get_pos() const =0;
	};
};
};
#endif
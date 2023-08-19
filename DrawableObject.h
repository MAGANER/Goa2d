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
	protected:
		SDL_Renderer* renderer = nullptr; //use it to draw

		DrawableObject(SDL_Renderer* renderer):renderer(renderer){}
		~DrawableObject(){}

		Vector2i size, pos;
	public:
		virtual void draw(const Vector2i& position) = 0;//draw at certain pos
		//TODO:: add method to draw object without passed position

		Vector2i const& get_size()const { return size; }
		Vector2i const& get_pos()const { return pos; }


		//this method is virtual because it probably changes SDL_Rect or something similar
		virtual void update_pos(const Vector2i& new_pos) = 0;
	};
};
};
#endif
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"DrawableObject.h"
#include"Color.h"
#include<iostream>
namespace Goat2d
{
namespace core
{
	class Rectangle :public DrawableObject
	{
		SDL_Rect* fill_rect = nullptr;
		Color color;
	public:
		Rectangle(const Vector2i& size, 
				  const Vector2i& pos,
				  const Color& color,
				  SDL_Renderer* renderer);
		~Rectangle();

		void draw(const Vector2i& position);

		Vector2i const& get_size()const { return Vector2i(fill_rect->w, fill_rect->y); }
		Vector2i const& get_pos() const { return Vector2i(fill_rect->x, fill_rect->y); };
	};
};

};
#endif
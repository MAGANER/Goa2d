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

		void set_color(const Color& color) { this->color = color; }
		void update_pos(const Vector2i& new_pos)
		{
			pos = new_pos;

			fill_rect->x = new_pos.x;
			fill_rect->y = new_pos.y;
		}
	};
};

};
#endif
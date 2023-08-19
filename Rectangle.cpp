#include"Rectangle.h"
using namespace Goat2d::core;

Rectangle::Rectangle(const Vector2i& size, 
					 const Vector2i& pos,
					 const Color& color,
					 SDL_Renderer* renderer) :DrawableObject(renderer)
{
	fill_rect = new SDL_Rect;

	fill_rect->x = pos.x;
	fill_rect->y = pos.y;
	fill_rect->w = size.x;
	fill_rect->h = size.y;
	this->color = color;

}
Rectangle::~Rectangle()
{
	if (fill_rect != nullptr)
		delete fill_rect;
}

void Rectangle::draw(const Vector2i& position)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, fill_rect);
}
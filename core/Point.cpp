#include"Point.h"
using namespace Goat2d::core;

Point::Point(const Vector2f& pos, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->pos = pos;
}
Point::Point(const Vector2f& pos, const Color& color, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->pos = pos;
	this->color = color;
}

void Point::draw()
{
	if (!visible)
		return;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPointF(renderer, pos.x, pos.y);
}
void Point::draw(const Vector2f& pos)
{
	if (!visible)
		return;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPointF(renderer, pos.x, pos.y);
}
void Point::update_pos(const Vector2f& new_pos)
{
	pos = new_pos;
}
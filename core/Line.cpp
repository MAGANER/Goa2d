#include"Line.h"
using namespace Goat2d::core;

Line::Line(const begin_end& points, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	pos = points.first;//start point
	end = points.second;
}
Line::Line(const begin_end& points, const Color& color, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->color = color;
	pos = points.first;//start point
	end = points.second;
}
Line::~Line()
{
}

void Line::draw()
{
	if (!visible)
		return;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLineF(renderer, pos.x, pos.y,end.x, end.y);
}
void Line::draw(const Vector2f& pos_start, const Vector2f& pos_end)
{
	if (!visible)
		return;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos_start.x, pos_start.y, pos_end.x, pos_end.y);
}
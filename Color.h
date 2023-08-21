#ifndef COLOR_H
#define COLOR_H
#include"SDL.h"
namespace Goat2d
{
namespace core
{
	typedef SDL_Color Color;

	static inline Color make_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		return Color{.r=r,.g=g,.b=b,.a=a};
	}
	static inline void copy_color(Color* dest, Color* source)
	{
		//TODO::add checks if those pointers aren't nulls

		dest->r = source->r;
		dest->g = source->g;
		dest->b = source->b;
		dest->a = source->a;
	}
};
};
#endif
#ifndef FLIP_TYPE_H
#define FLIP_TYPE_H
#include"SDL.h"
namespace Goat2d
{
namespace core
{
	enum class FlipType :short
	{
		None       = SDL_FLIP_NONE,
		Vertical   = SDL_FLIP_VERTICAL,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Diagonal   = Vertical | Horizontal
	};
};
};
#endif
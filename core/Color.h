/*!
\file
\brief several functions to use SDL_Color structure
\author Maganer
\version 0.1
\date 02.09.2023

There is no need to create custom class for Color, because
it's very simple structure object, but there is sense to 
have handy functions to work with raw C structures.
*/

#ifndef COLOR_H
#define COLOR_H
#include"SDL.h"

//! whole framework
namespace Goat2d
{

//! SDL overwrapper
namespace core
{
	//! a synonym to SDL_Color
	typedef SDL_Color Color;


	/**
	 * @brief copy color pointer's value to another one
	 *
	 * @param dest Description of the first parameter
	 * @param source Description of the second parameter
	 *
	 * @return nothing
	 */
	static inline void copy_color(Color* dest, Color* source)
	{
		if (dest == nullptr or source == nullptr)
		{
			print_error("can't copy color because pointer is nullptr!");
			write_error("can't copy color because pointer is nullptr!");
			return;
		}

		dest->r = source->r;
		dest->g = source->g;
		dest->b = source->b;
		dest->a = source->a;
	}

	/**
	 * @brief compare RGBA values of color pointers
	 *
	 * @param a the first color to compare
	 * @param b the second color to compare
	 *
	 * @return true if colors are equal, otherwise it returns false
	 */
	static inline bool compare_colors(Color* a, Color* b)
	{
		if (a == nullptr or b == nullptr)
		{
			print_error("can't compare colors because some of them is nullptr!");
			write_error("can't compare colors because some of them is nullptr!");
			return false;
		}
		return a->r == b->r and
			   a->b == b->b and
			   a->g == b->g and
			   a->a == b->a;
	}
};
};

#define BLACK   Goat2d::core::Color(.r=0,  .g=0,  .b=0,   .a=0)
#define WHITE   Goat2d::core::Color(.r=255,.g=255,.b=255, .a=255)
#define RED     Goat2d::core::Color(.r=255,.g=0,  .b=0,   .a=255)
#define GREEN   Goat2d::core::Color(.r=0,  .g=255,.b=0,   .a=255)
#define	BLUE    Goat2d::core::Color(.r=0,  .g=0,  .b=255, .a=255)
#define YELLOW  Goat2d::core::Color(.r=255,.g=255,.b=0,   .a=255)
#define MAGENTA Goat2d::core::Color(.r=255,.g=0,  .b=255, .a=255)
#define CYAN    Goat2d::core::Color(.r=0,  .g=255,.b=255, .a=255)
#endif
/*!
\file
\brief Base class for every object that can be drawn: textures, primitives, text.
\author Maganer
\version 0.1
\date 02.09.2023

Every drawable entity must be inherited from this class.
*/


#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include"SDL.h"
#include"Vector.h"
namespace Goat2d
{
namespace core
{
	/*!
	\brief Base class for every drawable object
	\author MAGANER
	\date 10.09.2023

	Base class for every object that can be drawn: textures, primitives, text.
	Every drawable entity must be inherited from this class.
	*/
	class DrawableObject
	{
	protected:
		//this pointer has an address of renderer that was initialised in GameWindow class
		//so you shouldn't init/delete it, just use it for SDL functions, where it's required

		//! Can not be changed, pointer to Window's render
		SDL_Renderer* renderer = nullptr; //use it to draw

		DrawableObject(SDL_Renderer* renderer):renderer(renderer){}
		~DrawableObject(){}

		//! common properties of every object
		Vector2i size, pos;
	public:
		virtual void draw() = 0;

		Vector2i const& get_size()const { return size; }
		Vector2i const& get_pos()const { return pos; }


		//this method is virtual because it probably changes SDL_Rect or something similar
		virtual void update_pos(const Vector2i& new_pos) = 0;
	};
};
};
#endif
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

		//! overwrapper for flipping types of SDL
		enum class FlipType:short
		{
			None = -1,
			Horizontal = SDL_FLIP_HORIZONTAL,
			Vertical   = SDL_FLIP_VERTICAL,
			Diagonal   = Horizontal | Vertical
		};
	private:

		//! object will be drawn rotated by this angle
		float rotation_angle = 0.0f;
		FlipType flipping_type = FlipType::None;
	protected:
		//this pointer has an address of renderer that was initialised in GameWindow class
		//so you shouldn't init/delete it, just use it for SDL functions, where it's required

		//! Can not be changed, pointer to Window's render
		SDL_Renderer* renderer = nullptr; //use it to draw

		DrawableObject(SDL_Renderer* renderer):renderer(renderer){}
		~DrawableObject(){}

		//! common properties of every object
		Vector2f pos;
		Vector2i size;


		//! if it's false then object won't be drawn. it's true by default
		bool visible = true;
	public:
		virtual void draw() = 0;
		virtual void draw(const Vector2f& pos) = 0;

		Vector2i const& get_size()const { return size; }
		Vector2f const& get_pos()const { return pos; }


		bool is_visible() { return visible; }
		
		float get_rotation_angle() { return rotation_angle; }
		FlipType get_flipping_type() { return flipping_type; }

		//! toggle object's visibility
		void make_visible(bool flag) { visible = flag; }

		//this method is virtual because it probably changes SDL_Rect or something similar
		virtual void update_pos(const Vector2f& new_pos) = 0;

		void set_rotation(float angle) { rotation_angle = angle; }
		void set_flipping_type(FlipType type) { flipping_type = type; }
	};
};
};
#endif
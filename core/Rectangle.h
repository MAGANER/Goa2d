/*!
\file
\brief Wrapper class for colored/outlined primitive - rectangle.
\author Maganer
\version 0.1
\date 02.09.2023

This class is based on DrawableObject, but almost everything in core
is just overwrapper for some low-level SDL features.
So Rectangle is convenient class to draw/move/change color
of low-level primitive.
*/


#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"DrawableObject.h"
#include"Color.h"
#include<tuple>
#include<utility>

namespace Goat2d
{
namespace core
{
	//! position, size and its filling color
	typedef std::tuple<Vector2f, Vector2f, Color> rect_data;

	//! outline width and its color
	typedef std::pair<int, Color> outline_rect_data;


	/*!
	\brief Class that represents basic  rectangle primitive.
	\author MAGANER
	\date 10.09.2023
	*/
	class Rectangle :public DrawableObject
	{
		//! contains position and size
		SDL_FRect* fill_rect = nullptr; 

		//! outline colored rectangle
		SDL_FRect* outline = nullptr; 

		//! rectangle can have no outline, so outline color is nullptr
		Color* outline_color = nullptr; 

		//! color that fills entire rect
		Color* color = nullptr; 
	public:

		/*!
		\brief Creates rectangle without outline
		\param[in] parameters tuple with position, size and its filling color
		\param[in] renderer Window's renderer
		*/
		Rectangle(const rect_data& parameters,
				  SDL_Renderer* renderer);

		/*!
		\brief create filled rect with outline
		\param[in] parameters tuple with position, size and its filling color
		\param[in] pair with outline width and its color
		\param[in] renderer Window's renderer
		*/
		Rectangle(const rect_data& parameters,
				  const outline_rect_data& outline_parameters,
				  SDL_Renderer* renderer);

		~Rectangle();

		//! draw rectangle
		void draw()override;

		//! draw rectangle at specific position. it doesn't change rect's own position
		void draw(const Vector2f& pos)override;

		//! change filling color
		void set_color(const Color& color);

		//! change outline border color
		void set_outline_color(const Color& color);


		//! change left top corner position
		void update_pos(const Vector2f& new_pos) override
		{
			pos = new_pos;

			//change position if it's not hollow rect
			if (fill_rect != nullptr)
			{
				fill_rect->x = new_pos.x;
				fill_rect->y = new_pos.y;
			}

			//change outline's position if it exists
			if (outline != nullptr)
			{
				outline->x = new_pos.x;
				outline->y = new_pos.y;
			}
		}
	};
};

};
#endif
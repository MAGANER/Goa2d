/*!
\file
\brief Class that represent primitive entity - point
\author Maganer
\version 0.1
\date 02.09.2023
*/


#ifndef POINT_H
#define POINT_H
#include"DrawableObject.h"
#include"Color.h"
namespace Goat2d
{
namespace core
{

	/*!
	\brief Simple overwrapper over basic point that can be renderer with SDL.
	\author MAGANER
	\date 10.09.2023
	*/
	class Point :public DrawableObject
	{
		//! default color is white
		Color color = Color(255, 255, 255, 255);
	public:
		/*!
		\brief Create white point at specific position
		\param[in] pos position to place point
		\param[in] renderer Window's renderer
		*/
		Point(const Vector2f& pos, SDL_Renderer* renderer);

		/*!
		\brief Create colored point at specific position
		\param[in] pos position to place point
		\param[in] color specific color to fill point
		\param[in] renderer Window's renderer
		*/
		Point(const Vector2f& pos, const Color& color, SDL_Renderer* renderer);

		~Point() {}


		//! draw point at current position
		void draw()override;

		//! set new point's position
		void update_pos(const Vector2f& new_pos)override;
	};
};
};
#endif
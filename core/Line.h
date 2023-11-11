/*!
\file
\brief A primitive class that represents line
\author Maganer
\version 0.1
\date 02.09.2023
*/


#ifndef LINE_H
#define LINE_H
#include"DrawableObject.h"
#include"Color.h"
#include<utility>
namespace Goat2d
{
namespace core
{
	//! second value is end point and first value is beginning point
	typedef std::pair<Vector2f, Vector2f> begin_end;


	/*!
	\brief overwrapper for SDL ability to render line
	\author MAGANER
	\date 10.09.2023
	*/
	class Line :public DrawableObject
	{
		//! DrawableObject's pos field is beginning point, so it's second line's point
		Vector2f end; 

		//! line's color, default is white
		Color color = Color(255, 255, 255, 255);
	public:

		/*!
		\brief Creates white line
		\param[in] points begin and end
		\param[in] renderer window's renderer pointer
		*/
		Line(const begin_end& points,SDL_Renderer* renderer);

		/*!
		\brief Creates colored line
		\param[in] points begin and end
		\param[in] color to fill the line
		\param[in] renderer window's renderer pointer
		*/
		Line(const begin_end& points,const Color& color, SDL_Renderer* renderer);
		~Line();

		//! draw lines at current  points
		void draw()override;


		//! don't use this function because you need to change 2 points
		[[deprecated]]
		void draw(const Vector2f& pos)override { return; }

		/*!
		\brief draw line at specific points
		\param[in] pos_start start point
		\param[in] pos_end end point
		*/
		void draw(const Vector2f& pos_start, const Vector2f& pos_end);

		//! don't use this function because you need to change 2 points
		[[deprecated]]
		void update_pos(const Vector2f& new_pos) override { return; }

		/*!
		\brief change position of line
		\param[in] new_pos_begin new position of start
		\param[in] new_pos_end new position of end
		*/
		void update_pos(const Vector2f& new_pos_begin, const Vector2f& new_pos_end)
		{
			pos = new_pos_begin;
			end = new_pos_end;
		}

		//! returns unchangable referense to end point
		Vector2f const& get_end_pos()const { return end; }
	};
};
};

#endif //LINE_H
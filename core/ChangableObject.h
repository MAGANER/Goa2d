/*!
\file
\brief Base class for every object that can be drawn and changed(rotated, flipped,scaled): textures and text.
\author Maganer
\version 0.2
\date 09.12.2023

Textures and Texts are inhereted from this class just like any other one that can be changed.
*/

#ifndef CHANGABLE_OBJECT_H
#define CHANGABLE_OBJECT_H
#include"DrawableObject.h"
namespace Goat2d
{
namespace core
{
	/*
	Note on flipping and rotation.
	There is no sense in single point flipping,
	so point class stays unchanged.
	*/

	//! overwrapper for flipping types of SDL
	enum class FlipType :short
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL,
		Diagonal = Horizontal | Vertical
	};

	/*!
	\brief Base class for drawable object that can be rotated, flipped, scaled.
	\author MAGANER
	\date 09.12.2023
	*/
	class ChangableObject: public DrawableObject
	{
	private:
		//! object will be drawn rotated by this angle
		double rotation_angle = 0.0f;

		//! flip object. No flipping by default
		FlipType flipping_type = FlipType::None;
	protected:
		ChangableObject(SDL_Renderer* renderer,
						double rotation_angle=0.0f,
						FlipType flipping_type=FlipType::None):
			DrawableObject(renderer),
			rotation_angle(rotation_angle),
			flipping_type(flipping_type)
		{}
	public:
		//! virtual method derived from DrawableObject
		virtual void draw() = 0;

		//! virtual method derived from DrawableObject
		virtual void draw(const Vector2f& pos) = 0;

		double get_rotation_angle() { return rotation_angle; }
		FlipType get_flipping_type() { return flipping_type; }

		void set_rotation(double angle) { rotation_angle = angle; }
		void set_flipping_type(FlipType type) { flipping_type = type; }
	};
};
};
#endif
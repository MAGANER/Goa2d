/*!
\file
\brief class that manages loading/deleting image files that can be used in game
\author Maganer
\version 0.1
\date 02.09.2023
*/

#include"core/Definitors.hpp"
#ifdef USE_SDL_IMG

#ifndef TEXTURE_H
#define TEXTURE_H
#include"core/DrawableObject.h"
#include"core/ErrorLogger.h"

namespace Goat2d
{
namespace core 
{

	/*!
	\brief Overwrapper class for low level representation of textures.
	\author MAGANER
	\date 10.09.2023
	*/
	class Texture: public DrawableObject
	{
		//! pixel data
		SDL_Texture* texture = nullptr;

		//! size, pos
		SDL_Rect* drawing_rect = nullptr;

		//! if it's true, than everything loaded correctly
		bool ok = true; 
	public:

		/*!
		\brief Creates texture object
		\param[in] path path to image that will be loaded as texture
		\param[in] renderer Window's renderer
		*/
		Texture(const std::string& path,SDL_Renderer* renderer);
		~Texture();

		//! renders textures on screen
		void draw()override;

		//! returns creation status
		bool is_ok()const { return ok; }

		//! set new position of left top corner
		void update_pos(const Vector2i& new_pos)override
		{
			pos = new_pos;

			drawing_rect->x = new_pos.x;
			drawing_rect->y = new_pos.y;
		}
	};
	

};
};
#endif //TEXTURE_H
#endif //USE_SDL_TTF
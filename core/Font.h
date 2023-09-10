/*!
\file
\brief Wrapper for low level SDL font. 
\author Maganer
\version 0.1
\date 02.09.2023

Safe overwrapper for SDL_ttf font.
*/


#include"Definitors.hpp"

#ifdef USE_SDL_TTF
#ifndef FONT_H
#define FONT_H
#include"SDL_ttf.h"
#include"ErrorLogger.h"
#include<string>
namespace Goat2d
{
namespace core
{

	/*!
	\brief Wrapper for low level SDL font. 
	\author MAGANER
	\date 10.09.2023
	*/
	class Font
	{
		//! pointer to SDL's structure, representing font file
		TTF_Font* font = nullptr;

		//! represents state of loading. True if ok, else False
		bool ok = true;
	public:

		/*!
		\brief Creates font of specified size
		\param[in] path ttf file's path
		\param[in] size glyph's size 
		*/
		Font(const std::string& path, int font_size)
		{
			font = TTF_OpenFont(path.c_str(), font_size);
			if (font == NULL)
			{
				print_error("Failed to load lazy font! SDL_ttf Error:");
				write_error("Failed to load lazy font! SDL_ttf Error:");
				ok = false;
			}
		}
		~Font()
		{
			TTF_CloseFont(font);
		}

		//!return constant pointer to SDL font structure
		TTF_Font const* get_font()const { return font; }

		//! returns status of file loading
		bool is_ok()const { return ok; }
	};
};
};
#endif //USE_SDL_TTF
#endif //FONT_H
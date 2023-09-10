/*!
\file
\brief overwrapper for Text. It works in the similar way with Texture class
\author Maganer
\version 0.1
\date 02.09.2023
*/


#include"Definitors.hpp"
#ifdef USE_SDL_TTF

#ifndef TEXT_H
#define TEXT_H
#include"DrawableObject.h"
#include"Font.h"
#include"Color.h"
namespace Goat2d
{
namespace core
{

	/*!
	\brief Overwrapper class for low level representation of text.
	\author MAGANER
	\date 10.09.2023
	*/
	class Text: public DrawableObject
	{
	private:

		//! false, if something went wrong with text creation
		bool ok = true; 

		//! inner representation of text
		SDL_Texture* text_texture = nullptr;

		//! position and size of text texture
		SDL_Rect* rect = nullptr;
		
		//! font should be deleted while text is being renderer
		Font* font;

		//! filling color
		Color color;
	public:

		/*!
		\brief Creates text object
		\param[in] font reference to font objects. it should be deleted while text is being renderer!
		\param[in] text string that will be renderer
		\param[in] pos position of left top corner
		\param[in] renderer Window's renderer
		\param[in] color filling color. Default value is white
		*/
		Text(const Font& font,
			 const std::string& text,
			 const Vector2i& pos,
			 SDL_Renderer* renderer,
			 const Color& color=Color(255,255,255,255));
		~Text();

		//! render text on window
		void draw() override;

		//! set new top left corner position
		void update_pos(const Vector2i& new_pos) override;

		//! set new filling color
		void set_color(const Color& color);

		//! returns creation status
		bool is_ok()const { return ok; }

		//! recreate Text object with new string
		Text* update_text(const std::string& text);
	};
};
};
#endif //TEXT_H
#endif //USE_SDL_TTF
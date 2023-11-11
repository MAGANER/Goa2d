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

		//! string that will be renderered
		std::string text;
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
			 const Vector2f& pos,
			 SDL_Renderer* renderer,
			 const Color& color=Color(255,255,255,255));
		~Text();

		//! render text on window
		void draw() override;

		//! render text on window with specific position. it doesn't change text's own position
		void draw(const Vector2f& pos) override;

		//! set new top left corner position
		void update_pos(const Vector2f& new_pos) override;

		//! apply new color to existing one
		void set_color_mod(const Color& color);

		//! returns creation status
		bool is_ok()const { return ok; }

		//! recreate Text object with new string(change color)
		Text* update_text(const std::string& text);

		//! recreate Text object with new color(change color)
		Text* update_text(const Color& color);

		//! return color
		Color const& get_color()const { return color; }
	};
};
};
#endif //TEXT_H
#endif //USE_SDL_TTF
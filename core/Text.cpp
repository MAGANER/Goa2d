#include"Text.h"
#ifdef USE_SDL_TTF

using namespace Goat2d::core;

Text::Text(const Font& font,
		   const std::string& text,
		   const Vector2f& pos,
		   SDL_Renderer* renderer,
		   const Color& color,
		   double rotation_angle,
		   FlipType flipping_type)
					:TransformableObject(renderer,rotation_angle/*, flipping_type*/),
					 font(const_cast<Font*>(&font)),
					 color(color),
					 text(text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(const_cast<TTF_Font*>(font.get_font()), 
												text.c_str(), color);
	if (surface == NULL)
	{
		print_error("Unable to render text surface! SDL_ttf Error:");
		write_error("Unable to render text surface! SDL_ttf Error:");
		ok = false;
	}
	else
	{
		text_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (text_texture == NULL)
		{
			print_error("Unable to create texture from rendered text! SDL Error:");
			write_error("Unable to create texture from rendered text! SDL Error:");
		}
		else
		{
			SDL_QueryTexture(text_texture, NULL, NULL, &size.x, &size.y);

			rect = new SDL_Rect;
			rect->x = pos.x;
			rect->y = pos.y;
			rect->w = size.x;
			rect->h = size.y;

			this->pos = pos;

		}

		//Get rid of old surface
		SDL_FreeSurface(surface);
	}

}
Text::~Text()
{
	SDL_DestroyTexture(text_texture);

	if (rect != nullptr)
		delete rect;
}
void Text::draw()
{
	if (!visible)
		return;

	SDL_RenderCopyEx(renderer,
		text_texture,
		NULL,
		rect,
		get_rotation_angle(),
		NULL,
		(SDL_RendererFlip)get_flipping_type());
}
void Text::draw(const Vector2f& pos)
{
	if (!visible)
		return;

	SDL_Rect r;
	r.x = pos.x;
	r.y = pos.y;
	r.w = rect->w;
	r.h = rect->h;
	SDL_RenderCopyEx(renderer,
		text_texture,
		NULL,
		&r,
		get_rotation_angle(),
		NULL,
		(SDL_RendererFlip)get_flipping_type());
}
void Text::update_pos(const Vector2f& new_pos)
{
	pos = new_pos;
	rect->x = pos.x;
	rect->y = pos.y;
}
void Text::set_color_mod(const Color& color)
{
	SDL_SetTextureColorMod(text_texture, color.r, color.g, color.b);
}
Text* Text::update_text(const std::string& text)
{
	SDL_DestroyTexture(text_texture);
	delete rect;

	return new Text(*font, text, pos, renderer, color);
}
Text* Text::update_text(const Color& color)
{
	SDL_DestroyTexture(text_texture);
	delete rect;
	return new Text(*font, text, pos, renderer, color);
}
#endif
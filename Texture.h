#ifndef TEXTURE_H
#define TEXTURE_H
#include"SDL_image.h"
#include"ErrorLogger.h"
namespace Goat2d
{
namespace core 
{
	class Texture
	{
		SDL_Texture* texture = nullptr;
		bool ok = true;

		SDL_Renderer* renderer = nullptr; //use it to draw
	public:
		Texture(const std::string& path,SDL_Renderer* renderer);
		~Texture();

		void draw();
		bool is_ok()const { return ok; }
	};
	

};
};
#endif
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include"SDL.h"
#include<string>
#include<iostream>
namespace Goat2d
{
namespace core
{
	class GameWindow
	{
		//The window we'll be rendering to
		SDL_Window* window = nullptr;

		//The surface contained by the window
		SDL_Surface* screenSurface = nullptr;

		bool ok = false;
	public:
		GameWindow(int width, int height, const std::string& title);
		~GameWindow();

		bool is_ok() const { return ok; }
		void run();

	};
};
};


#endif //GAME_WINDOW_H
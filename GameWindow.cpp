#include"GameWindow.h"
using namespace Goat2d::core;

GameWindow::GameWindow(const GameWindowSetting& setting)
{
	print_error = setting._print_error;
	write_error = setting._write_error;

	if (SDL_Init(setting.SDL_subsystems) < 0)
	{
		if(print_error)::print_error("SDL could not initialize! SDL_Error:");
		if (write_error)::write_error("SDL could not initialize! SDL_Error:");
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(setting.title.c_str(),
								  setting.win_pos.x, 
								  setting.win_pos.y,
								  setting.win_size.x,
								  setting.win_size.y,
								  SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			if(print_error)::print_error("failed to create window: SDL_Error:");
			if (write_error)::write_error("failed to create window: SDL_Error:");
		}

		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		//Fill the surface black
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 
												     setting.background_color.r,
													 setting.background_color.g,
													 setting.background_color.b));

		//Update the surface
		SDL_UpdateWindowSurface(window);

		ok = true;
	}
}
GameWindow::~GameWindow()
{
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

void GameWindow::run()
{
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			//default event
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
}
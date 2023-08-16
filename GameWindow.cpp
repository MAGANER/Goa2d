#include"GameWindow.h"
using namespace Goat2d::core;

GameWindow::GameWindow(int width, int height, const std::string& title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//TODO::write debug info into log file
		std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(title.c_str(),
								  SDL_WINDOWPOS_UNDEFINED, 
								  SDL_WINDOWPOS_UNDEFINED, 
								  width, 
								  height, 
								  SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError() << std::endl;
		}

		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		//Fill the surface black
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

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
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
}
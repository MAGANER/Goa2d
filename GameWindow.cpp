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
			if(print_error)::print_error("failed to create window! SDL_Error:");
			if (write_error)::write_error("failed to create window! SDL_Error:");
		}
		else
		{
			//set it to false if any subsystem is not loaded correctly
			bool correct_init = false;

			//init img library
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				if (print_error)::print_error("SDL_image could not initialize! SDL_image Error:");
				if (write_error)::write_error("SDL_image could not initialize! SDL_image Error:");

				correct_init = true;
			}
			
			//init renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				if (print_error)::print_error("Renderer could not be created! SDL Error:");
				if (write_error)::write_error("Renderer could not be created! SDL Error:");
				correct_init = false;
			}
			else
			{
				correct_init = true;
			}

			if(correct_init)
			{				
				//Update the surface
				SDL_UpdateWindowSurface(window);

				ok = true;
				add_quit_event();

				start = SDL_GetTicks();
				FPS = setting.FPS;
				background_color = setting.background_color;
			}
		}
	}
}
GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	if (quit_event != nullptr)
		delete quit_event;
}
void GameWindow::run()
{
	SDL_Event e;
	while (!quit)
	{
		if (SDL_WaitEvent(&e) != 0)
		{
			quit_event->process((void*)&e);
			process_keyboard_events(e);
		}
		process_game_events();

		draw();
		wait();
	}
}
void GameWindow::add_quit_event()
{
	//default event to process quit button pressing
	auto pred = [](const SDL_Event& e) -> bool
	{
		return e.type == SDL_QUIT;
	};
	auto fn = [&](void* state) -> void
	{
		if (state != ZERO_STATE)
		{
			bool* val = static_cast<bool*>(state);
			*val = true;
		}
	};

	quit_event = new framework::KeyboardEvent(pred, fn, (void*)&this->quit);
}
void GameWindow::wait()
{
	//set fps framerate
	if (1000 / FPS > SDL_GetTicks() - start) 
	{
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
void GameWindow::draw()
{
	SDL_SetRenderDrawColor(renderer, background_color.r,
									 background_color.g,
									 background_color.b,
									 background_color.a);
	SDL_RenderClear(renderer);
	draw_current_scene();
	SDL_RenderPresent(renderer);
}
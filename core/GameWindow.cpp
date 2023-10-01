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
								  get_window_mode(setting));
		if (window == NULL)
		{
			if(print_error)::print_error("failed to create window! SDL_Error:");
			if (write_error)::write_error("failed to create window! SDL_Error:");
		}
		else
		{
			///My little note on correct_init 
			///CppCheck says there are several problems connected to this variable,
			/// but we change it to false/true because there are several init functions calls
			/// so we if one doesn't work then everything else won't work too, so ignore
			/// this CppCheck's note.
			/// P.S. I think there can be some more elegant way to init all required 
			
			//set it to false if any subsystem is not loaded correctly
			bool correct_init = true;

			//set  fullscreen if required and if it fails, than we can't init 
			correct_init = set_window_fullscreen_mode(setting);


	#ifdef USE_SDL_IMG
			//init img library
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				if (print_error)::print_error("SDL_image could not initialize! SDL_image Error:");
				if (write_error)::write_error("SDL_image could not initialize! SDL_image Error:");

				correct_init = false;
			}
	#endif //USE_SDL_IMG

	#ifdef USE_SDL_TTF
			//init ttf library
			if (TTF_Init() == -1)
			{
				if (print_error)::print_error("SDL_ttf could not initialize! SDL_ttf Error:");
				if (write_error)::write_error("SDL_ttf could not initialize! SDL_ttf Error:");
				correct_init = false;
			}
	#endif //USE_SDL_TTF


	#ifdef USE_SDL_AUDIO
			//init audio library
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
			{
				if (print_error)::print_error("SDL_mixer could not initialize! SDL_mixer Error:");
				if (write_error)::write_error("SDL_mixer could not initialize! SDL_mixer Error:");
				correct_init = false;
			}
	#endif // USE_SDL_AUDIO


			//init renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				if (print_error)::print_error("Renderer could not be created! SDL Error:");
				if (write_error)::write_error("Renderer could not be created! SDL Error:");
				correct_init = false;
			}

			if(correct_init)
			{				
				//Update the surface
				SDL_UpdateWindowSurface(window);

				ok = true;//everything worked fine
				add_quit_event();//create event to check should window be closed


				start = SDL_GetTicks();//used by frame rate limiter
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

	SDL_Quit();

	#ifdef USE_SDL_TTF
		TTF_Quit();
	#endif
	#ifdef USE_SDL_IMG
		IMG_Quit();
	#endif
	#ifdef USE_SDL_AUDIO
		Mix_Quit();
	#endif

	if (quit_event != nullptr)
		delete quit_event;

	if (icon != nullptr)
		SDL_FreeSurface(icon);
}
void GameWindow::run()
{
	if (get_current_scene_id() == -1)
	{
		::print_error("GameWindow error: no scene added!\n");
		::write_error("GameWindow error: no scene added!\n");
		exit(-1);
	}
	//main game cycle

	//check and process keyboard events
	//process event of scene
	//draw and wait a bit to set FPS limit

	SDL_Event e;
	while (!quit)
	{
		if (should_change())
		{
			auto next_scene_id = get_next_id();
			if (!change_scene(next_scene_id))
			{
				std::cout << "can't change scene!";
			}
		}

		if (SDL_WaitEvent(&e) != 0)
		{
			quit_event->process(static_cast<void*>(&e));
			process_keyboard_events(e);

			for (auto& event : global_keyboard_events)
				event->process(static_cast<void*>(&e));
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
		//if user press X on window, then it's time to quit window
		return e.type == SDL_QUIT;
	};
	auto fn = [&](void* state) -> void
	{
		//if pred returns true, then we change quit variable's value to true
		if (state != ZERO_STATE)
		{
			bool* val = static_cast<bool*>(state);
			*val = true;
		}
	};

	//bind predicat, function and state together to get event
	quit_event = new framework::KeyboardEvent(pred, fn, static_cast<void*>(&this->quit));
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
Uint32 GameWindow::get_window_mode(const GameWindowSetting& setting)
{
	if (setting.resizable) //and not fullscreen
	{
		return SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	}
	// if fullscreen and resizable

	//return default window mode
	return SDL_WINDOW_SHOWN;
}
bool GameWindow::set_window_fullscreen_mode(const GameWindowSetting& setting)
{
	//skip if there is no need to set fullscreen mode
	if (!setting.false_fullscreen and !setting.true_fullscreen)
		return true;

	//you can set only 1 mode
	if (setting.false_fullscreen == setting.true_fullscreen)
	{
		if (print_error)::print_error("Can't set fullscreen mode! Choose true xor false fullscreen mode!");
		if (write_error)::write_error("Can't set fullscreen mode! Choose true xor false fullscreen mode!");
		return false;
	}
	else
	{
		auto mode = setting.false_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN;
		
		auto code = SDL_SetWindowFullscreen(window, mode);
		if (code == 0) 
			return true;

		if(print_error)
			::print_error("Failed to set fullscreen mode! SDL_Error:");
		if (write_error)
			::write_error("Failed to set fullscreen mode! SDL_Error:");
		return false;
	}
}
bool GameWindow::set_true_fullscreen_mode()
{
	if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0)
	{
		if (print_error)
			::print_error("Failed to set fullscreen mode! SDL_Error:");
		if (write_error)
			::write_error("Failed to set fullscreen mode! SDL_Error:");
		return false;
	}
	return true;
}
bool GameWindow::set_false_fullscreen_mode()
{
	if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
	{
		if (print_error)
			::print_error("Failed to set fullscreen mode! SDL_Error:");
		if (write_error)
			::write_error("Failed to set fullscreen mode! SDL_Error:");
		return false;
	}
	return true;
}
bool GameWindow::set_icon(const std::string& icon_image_path)
{
	icon = IMG_Load(icon_image_path.c_str());
	if (icon == NULL)
	{
		if (print_error)::print_error("Failed to load icon " + icon_image_path + "! SDL_Error:");
		if (print_error)::write_error("Failed to load icon " + icon_image_path + "! SDL_Error:");
		return false;
	}

	SDL_SetWindowIcon(window, icon);
	return true;
}
void GameWindow::add_global_keyboard_event(framework::KeyboardEvent* event)
{
	global_keyboard_events.push_back(event);
}
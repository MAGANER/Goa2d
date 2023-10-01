/*!
\file
\brief Contains GameWindow that obtains scenes to process and GameWindowSetting to customize window's setting
\author Maganer
\version 0.1
\date 02.09.2023
*/


#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include"Definitors.hpp"

#ifdef USE_SDL_TTF
#include"SDL_ttf.h"
#endif

#ifdef USE_SDL_AUDIO
#include"SDL_mixer.h"
#endif

#ifdef USE_SDL_IMG
#include "SDL_image.h"
#endif

#include"framework/SceneManager.h"
#include"ErrorLogger.h"

#include<string>

namespace Goat2d
{
namespace core
{
	/*
	* GameWindowSetting is structure that contains parameters,
	* that should be provided to GameWindow class to set its initial state
	*/

	//! contains setting for window. It was created to prevent too many arguments of GameWindow's constructor
	struct GameWindowSetting
	{
		//! SDL_INIT_VIDEO or SDL_INIT_VIDEO | SDL_INIT_AUDIO e.t.c
		int SDL_subsystems; 

		//! window's name
		std::string title;

		//! clearing color
		Color background_color;

		//! error processing flags
		bool _print_error, _write_error;

		//! start position and width, height pair
		Vector2i win_pos, win_size;

		//! FPS limit
		int FPS;

		//! window's ability to change its width and height
		bool resizable;

		//! "real" fullscreen with a videomode change
		bool true_fullscreen;

		//! "fake" fullscreen that takes the size of the desktop; and 0 for windowed mode
		bool false_fullscreen;


		/*!
		\brief creates default window's setting
		*/
		GameWindowSetting():SDL_subsystems(SDL_INIT_VIDEO),
						    win_size(Vector2i(720,640)),
							title("Goat2d"),
							background_color(Color(0,0,0,255)),
							_print_error(true),
							_write_error(true),
							win_pos(Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
							FPS(30),
			                resizable(false),
							true_fullscreen(false),
							false_fullscreen(false)
		{
			//create default game window settings
		}


		/*!
		\brief creates window's setting based on already existed setting
		\param[in] setting reference to Setting structure object
		*/
		GameWindowSetting(const GameWindowSetting& setting):
						    SDL_subsystems(setting.SDL_subsystems),
						    win_size(setting.win_size),
							title(setting.title),
							background_color(setting.background_color),
							_print_error(setting._print_error),
							_write_error(setting._write_error),
							win_pos(setting.win_pos),
							FPS(setting.FPS),
							resizable(setting.resizable),
							true_fullscreen(setting.true_fullscreen),
							false_fullscreen(setting.false_fullscreen)
		{
			//fully customized window setting by user based on another setting
		}


		/*!
		\brief creates window from required systems and size. Suitable for testing.
		\param[in] SDL_subsystems systems that should be init
		\param[in] win_size window's width and height
		*/
		GameWindowSetting(int SDL_subsystems,
						  const Vector2i& win_size):
						  title("Goat2d"),
						  SDL_subsystems(SDL_subsystems),
						  win_size(win_size),
						  background_color(Color(0, 0, 0, 255)),
						  _print_error(true),
						  _write_error(true),
						  win_pos(Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
						  FPS(30),
						  resizable(false),
						  true_fullscreen(false),
						  false_fullscreen(false)
		{
			//set only window size and required sdl subsystems
		}

		~GameWindowSetting(){}

	};

	/*!
	\brief GameWindow is class that is used to process game scene.
	\author MAGANER
	\date 10.09.2023

	Being derived from Scene manager it can add,change,process,draw .e.t.c
	each game scene.
	After the creation you should set scenes and check is everything ok to
	be sure the program won't crush.
	*/
	class GameWindow: public framework::SceneManager
	{
		//! The window we'll be rendering to
		SDL_Window* window = nullptr;

		//! The window renderer
		SDL_Renderer* renderer = nullptr;
		

		//! clearing color
		Color background_color;

		//! if window is created sucessfully variable's value is true 
		bool ok = false; 

		//! set true to quit window
		bool quit = false; 
		
		//! flags show should game window do this actions
		bool print_error, write_error;


		//! special hard coded event : press X to close window
		framework::KeyboardEvent* quit_event = nullptr;


		//! these keyboard events can be invoked in every scene of game
		std::list<framework::KeyboardEvent*> global_keyboard_events;

		//! time from starting SDL systems
		Uint32  start; 

		//! FPS counter
		int  FPS;


		//! icon for the window
		SDL_Surface* icon = nullptr;
	public:
		/*!
		\brief creates window from passed setting
		\param[in] setting reference to Setting structure object
		*/
		GameWindow(const GameWindowSetting& setting);
		~GameWindow();

		//! returns the state of window creation. True if ok, else False
		bool is_ok() const { return ok; }

		//! execute game cycle
		void run();

		//! should be passed to the scene constructor.
		SDL_Renderer* get_renderer() { return renderer; }

		//! set "real" fullscreen with a videomode change
		bool set_true_fullscreen_mode();

		//! "fake" fullscreen that takes the size of the desktop; and 0 for windowed mode
		bool set_false_fullscreen_mode();

		//! change default window's icon to custom one
		bool set_icon(const std::string& icon_image_path);

		//! add keyboard event that is common for all games(set on/off fullscreen for example)
		void add_global_keyboard_event(framework::KeyboardEvent* event);
	private:

		//! create quit event used by window
		void add_quit_event();

		//! set FPS limit
		void wait();


		//! render current scene
		void draw();

		//! it's always shown, but it optionally can be fullscreen or resizable
		Uint32 get_window_mode(const GameWindowSetting& setting);


		//! set window mode at the creation of window
		bool set_window_fullscreen_mode(const GameWindowSetting& setting);
	};
};
};
#endif //GAME_WINDOW_H
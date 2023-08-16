#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include"ErrorLogger.h"
#include"Color.h"
#include"Vector.h"
namespace Goat2d
{
namespace core
{
	/*
	* GameWindowSetting is structure that contains parameters,
	* that should be provided to GameWindow class to set its initial state
	*/
	struct GameWindowSetting
	{
		int SDL_subsystems; //SDL_INIT_VIDEO or SDL_INIT_VIDEO | SDL_INIT_AUDIO e.t.c
		std::string title;
		Color background_color;
		bool _print_error, _write_error;
		Vector2i win_pos, win_size;

		GameWindowSetting()
		{
			SDL_subsystems = SDL_INIT_VIDEO;
			win_size = Vector2i(720, 640);
			title = "Goat2d";
			background_color = Color(0, 0, 0, 255);
			_print_error = true;
			_write_error = true;
			win_pos = Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}
		GameWindowSetting(const GameWindowSetting& setting)
		{
			SDL_subsystems = setting.SDL_subsystems;
			win_size = setting.win_size;
			title = setting.title;
			background_color = setting.background_color;
			_print_error = setting._print_error;
			_write_error = setting._write_error;
			win_pos = setting.win_pos;
		}
		GameWindowSetting(int SDL_subsystems,
						  const Vector2i& win_size)
		{
			this->SDL_subsystems = SDL_subsystems;
			this->win_size = win_size;
			std::cout << win_size.x << " " << win_size.y << std::endl;
			background_color = Color(0, 0, 0, 255);
			_print_error = true;
			_write_error = true;
			win_pos = Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}
		GameWindowSetting(int SDL_subsystems,
						  const Vector2i& win_size,
						  const Vector2i& win_pos,
						  const std::string& title,
						  const Color& background_color,
						  bool _print_error,
						  bool _write_error)
		{
			this->SDL_subsystems = SDL_subsystems;
			this->win_size = win_size;
			this->background_color = background_color;
			this->_print_error = _print_error;
			this->_write_error = _write_error;
			this->win_pos = win_pos;
		}
		~GameWindowSetting(){}

	};

	class GameWindow
	{
		//The window we'll be rendering to
		SDL_Window* window = nullptr;

		//The surface contained by the window
		SDL_Surface* screenSurface = nullptr;

		bool ok = false;
		bool print_error, write_error;
	public:
		GameWindow(const GameWindowSetting& setting);
		~GameWindow();

		bool is_ok() const { return ok; }
		void run();

	};
};
};
#endif //GAME_WINDOW_H
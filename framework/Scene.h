/*!
\file
\brief Base class for every scene in game
\author Maganer
\version 0.1
\date 02.09.2023


BaseScene is one of the core ideas. It contains events,
provided by event manager. They express everything that happens in game,
also they are used to check and process keyboard/mouse/joystick events.

So when you start to write your game, you start writing some scene.
Main menu,for example. It contains some textual data, buttons and
events like clicking,e.t.c
*/

#ifndef SCENE_H
#define SCENE_H
#include"Event.h"
#include"core/Texture.h"
#include"core/Rectangle.h"
#include"core/Line.h"
#include"core/Point.h"
#include"core/Vector.h"
#include"core/Font.h"
#include"core/Text.h"
#include"core/Color.h"
namespace Goat2d
{
namespace framework
{

	/*!
	\brief Base class for every scene in game.
	\author MAGANER
	\date 10.09.2023

	*/
	class BaseScene
	{
	private:
		//! pointer to window's renderer
		SDL_Renderer* renderer; 
	protected:
		EventManager event_manager;

		//! if true than should switch to another scene
		bool should_change = false; 

		//! data that can be passed to next scene
		void* return_value = nullptr;

		//! current scene id
		int id = 0; 
		
		//! next scene id that should be executed after current one
		int next_id = -1;


		//! this variable is used to avoid relying on CPU
		double delta_time = 1.0;
	public:
		/*
			use it if scene needs to toggle fullscreen
		*/
		enum class FullscreenModes
		{
			None, //don't do anything
			False,
			True,
			NoFullscreen
		};
		void toggled() { mode_to_set = FullscreenModes::None; }
	protected:
		FullscreenModes mode_to_set = FullscreenModes::None;
	public:
		/*!
		\brief bound scene with basic information
		\param[in] id unique number that makes scene different
		\param[in] Window's renderer
		*/
		BaseScene(int id, SDL_Renderer* renderer):id(id),renderer(renderer){}
		virtual ~BaseScene(){}

		//! abstract method to draw scene
		virtual void render() = 0;

		//! get reference to object that is used to manage events
		EventManager& get_event_manager() { return event_manager; }
		
		void set_delta_time(double time) { delta_time = time; }

		//! should scene be changed to another one
		bool change()const { return should_change; }

		//! get data that should be passed to the next scene
		void const* get_return_value()const { return return_value; }

		//! get current scene id
		int get_id()const { return id; }

		//! get next scene id
		int get_next_id()const { return next_id; }

		//! get Window's renderer
		SDL_Renderer* get_renderer() { return renderer; }

		FullscreenModes get_fullscreen_mode_to_change() { return mode_to_set; }

		//! get current renderer's width and height
		core::Vector2i get_renderer_size()const
		{
			int w, h;
			SDL_GetRendererOutputSize(renderer, &w, &h);
			return core::Vector2i(w, h);
		}

		//these functions are used by SceneManager
		//so you don't need to call them

		//! inner function to process keyboard's events
		void process_keyboard_events(SDL_Event& _event)
		{
			for (auto& e : event_manager.get_keyboard_events())
				e->process(static_cast<void*>(&_event));
		}

		//! inner function to process in-game scene's events
		void process_game_events()
		{
			for (auto& e : event_manager.get_nonconditional_events())
				e->process();
			for (auto& e : event_manager.get_conditional_events())
				e->process();
		}
	protected:

		//create texture/rect/another primitive based on current renderer

		//these methods is used by children to avoid working with private renderer pointer
		//because it's incapsulated and unable to be used by other classes
		
		//these function are dedicated to framework's user to simplify creation of game objects

	#ifdef USE_SDL_IMG
		/*!
		\brief create texture. It doesn't require renderer, because its pointer is already stored
		\param[in] path path to image texture
		\return pointer to Texture object
		\warning you can use this function only if USE_SDL_IMG is defined in core/Definitors.h
		*/
		inline core::Texture* create_texture(const std::string& path)
		{
			return new core::Texture(path, renderer);
		}
	#endif
		/*!
		\brief create rectangle without outline. It doesn't require renderer, because its pointer is already stored
		\param[in] parameters position, size and its filling color
		\return pointer to Rectangle class
		*/
		inline core::Rectangle* create_rect(const core::rect_data& parameters)
		{
			return new core::Rectangle(parameters,renderer);
		}
		/*!
		\brief create rectangle with outline. It doesn't require renderer, because its pointer is already stored
		\param[in] parameters position, size and its filling color
		\param[in] outline_params outline width and color
		\return pointer to Rectangle class
		*/
		inline core::Rectangle* create_outlined_rect(const core::rect_data& parameters,
													 const core::outline_rect_data& outline_params)
		{
			return new core::Rectangle(parameters, outline_params, renderer);
		}

		/*!
		\brief create white line. It doesn't require renderer, because its pointer is already stored
		\param[in] points positions of start and end
		\return pointer to Line class
		*/
		inline core::Line* create_white_line(const core::begin_end& points)
		{
			return new core::Line(points, renderer);
		}

		/*!
		\brief create white line. It doesn't require renderer, because its pointer is already stored
		\param[in] points positions of start and end
		\param[in] color color to fill line
		\return pointer to Line class
		*/
		inline core::Line* create_colored_line(const core::begin_end& points, const core::Color& color)
		{
			return new core::Line(points, color, renderer);
		}

		/*!
		\brief create white point. It doesn't require renderer, because its pointer is already stored
		\param[in] point position
		\return pointer to Point class
		*/
		inline core::Point* create_white_point(const core::Vector2f& point)
		{
			return new core::Point(point, renderer);
		}

		/*!
		\brief create white point. It doesn't require renderer, because its pointer is already stored
		\param[in] point position
		\param[in] color color to fill Point
		\return pointer to Point class
		*/
		inline core::Point* create_colored_point(const core::Vector2f& point, const core::Color& color)
		{
			return new core::Point(point, color, renderer);
		}

	#ifdef USE_SDL_TTF
		/*!
		\brief create white Text. It doesn't require renderer, because its pointer is already stored
		\param[in] text string that will be rendered
		\param[in] pos position of left top corner
		\param[in] font pointer to Font object
		\return pointer to Text object
		\warning you can use this function only if USE_SDL_TTF is defined in core/Definitors.h
		*/
		inline core::Text* create_white_text(const std::string& text,const core::Vector2f& pos, core::Font* font)
		{
			return new core::Text(*font, text, pos, renderer);
		}

		/*!
		\brief create colored Text. It doesn't require renderer, because its pointer is already stored
		\param[in] text string that will be rendered
		\param[in] pos position of left top corner
		\param[in] color color to fill text
		\param[in] font pointer to Font object
		\return pointer to Text object
		\warning you can use this function only if USE_SDL_TTF is defined in core/Definitors.h
		*/
		inline core::Text* create_colored_text(const std::string& text, const core::Vector2f& pos, const core::Color& color, core::Font* font)
		{
			return new core::Text(*font, text, pos, renderer, color);
		}
	#endif
		//! set next scene's id
		void set_next_id(int id) { next_id = id; }
	};
};
};

#endif
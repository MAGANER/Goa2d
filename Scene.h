#ifndef SCENE_H
#define SCENE_H
#include"Event.h"
#include"Texture.h"
#include"Rectangle.h"
#include"Vector.h"
#include"Color.h"
namespace Goat2d
{
namespace framework
{
	class BaseScene
	{
	private:
		SDL_Renderer* renderer; //pointer to window's renderer
	protected:
		EventManager event_manager;
		bool should_change = false;

		void* return_value = nullptr;
		int id = 0;
	public:
		BaseScene(int id, SDL_Renderer* renderer):id(id),renderer(renderer){}
		~BaseScene(){}

		
		virtual void render() = 0;
		void process_keyboard_events(SDL_Event& _event)
		{
			for(auto& e: event_manager.get_keyboard_events())
				e->process(static_cast<void*>(&_event));
		}
		void process_game_events()
		{
			for (auto& e : event_manager.get_conditional_events())
				e->process();
			for (auto& e : event_manager.get_nonconditional_events())
				e->process();
		}


		EventManager& get_event_manager() { return event_manager; }
		bool change()const { return should_change; }
		void const* get_return_value()const { return return_value; }
		int get_id()const { return id; }
	protected:

		//this method is used by children to avoid working with private renderer pointer
		//because it's incapsulated and unable to be used by other classes
		inline core::Texture* create_texture(const std::string& path)
		{
			return new core::Texture(path, renderer);
		}

		inline core::Rectangle* create_rect(const core::Vector2i& size,
											const core::Vector2i& pos,
											const core::Color& color)
		{
			return new core::Rectangle(size, pos, color, renderer);
		}
	};
};
};

#endif
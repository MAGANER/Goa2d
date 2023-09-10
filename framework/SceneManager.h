/*!
\file
\brief class that is used to manage scenes. Add, run, change.
\author Maganer
\version 0.1
\date 02.09.2023

This class is base for GameWindow, since game window
only gets the scenes and then pass it to scene manager
to get current scene to process/draw.
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include"Scene.h"
#include<unordered_map>
namespace Goat2d
{
namespace framework
{
	//! lambda that generates Scene
	typedef std::function<BaseScene* (void* prev_scene_ret_val)> gen_scene_fn;


	/*!
	\brief class to manipulate scenes.
	\author MAGANER
	\date 10.09.2023

	It stores, creates, updates and runs scenes.
	*/
	class SceneManager
	{
		//! stores scenes generators, where key is id and value is lambda to generate scene
		std::unordered_map<int, gen_scene_fn> scenes;

		//! current scene id to create
		int current_scene_id = -1;

		//! pointer to the created scene
		BaseScene* current_scene = nullptr;
	public:
		SceneManager(){}
		~SceneManager(){}

		/*!
		\brief add new scene generator with associated id
		\param[in] id special and unique number for a scene
		\param[in] generator lambda function that creates scene with associatted id
		\warning it doesn't check is id unique! SO IT MUST BE DONE IN NEXT VERSIONS!
		*/
		void add_scene(int id,const gen_scene_fn& generator);

		/*!
		\brief create new scene with associated id
		\param[in] id scene's id to create
		\warning it doesn't check is id available! SO IT MUST BE DONE IN VERSIONS!
		*/
		void set_start_scene_id(int id) 
		{ 
			current_scene_id = id; 
			current_scene = scenes[id](ZERO_STATE);//create start scene
		}
	protected:
		//! process current scene keyboard events
		void process_keyboard_events(SDL_Event& event);

		//! process game events of current scene
		void process_game_events();

		//! call current's scene draw method
		void draw_current_scene();

		//! get scene's id that must be executed after current one
		int get_next_id() { return current_scene->get_next_id(); }

		//! should set new scene
		bool should_change();

		//! change current scene to another one
		bool change_scene(int id_scene);
	};
};
};

#endif
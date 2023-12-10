/*!
\file
\brief Abstract class and particular ones to represent game actions.
\author Maganer
\version 0.1
\date 02.09.2023
*/
#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include<list>
#include<initializer_list>
#include"SDL.h"
#include"core/ErrorLogger.h"

#define ZERO_STATE static_cast<void*>(nullptr)
#define ALWAYS_RET_T [](void* e){ return true;}
namespace Goat2d
{

//! contains architectural classes
namespace framework
{
	//! boolean function that checks is event happened
	typedef std::function<bool(void* event)> predicat_t;

	//! action that must be executed when predicat returns true
	typedef std::function<void(void* state)> simple_callback_t;

	/// set of able events
	enum class EventType:unsigned short
	{
		nonconditional,///< doesn't require any condition to be executed
		conditional, ///< requires special condition to be executed
		keyboard ///< relates to keyboard actions
	};


	/*!
	\brief Every event must inherit this class.
	\author MAGANER
	\date 10.09.2023

	T is predicat class, F is action class E is class of event.
	Event is another core idea of the Goat2d framework.
	It combines condition(it can be fn-> true, that means always return true)
	and action applied to this condition, so you don't need to write
	bunch of if-elses, just create event inside the scene and pass it to
	the event manager.
	*/
	template<class T, class F>
	class BaseEvent
	{
	private:
		//! counts total number of created objects
		static inline size_t object_counter = 0;

		//! new event's id can't be equal or less than last one's id 
		static inline size_t last_id = 0;

		//! unique number for every event
		size_t id;

		//! this event won't be runned if it's disabled
		bool disable = false;
	protected:
		//! lambda that checks condition to execute action
		T predicat;

		//! action to execute
		F fn;

		//! event's type
		EventType type;

		//! outer data that is changed by event (it can be nullptr, so event doesn't change anything)
		void* state; 
	public:
		/*!
		\brief Add all required information to event
		\param[in] predicat lambda to check condition
		\param[in] fn action that must be executed if predicat returns true
		\param[in] state that can be used by predicat or action. It can be nullptr
		\param[in] type type of event
		*/
		BaseEvent(const T& predicat, 
				  const F& fn, 
				  void* state,
				  EventType type):predicat(predicat),fn(fn),state(state),type(type)
		{
			++object_counter;
			id = object_counter;
			last_id = id;
		}
		virtual ~BaseEvent() {}


		//! gets outer state and then process event
		virtual void process(void* event) = 0;

		//! process event without outer state
		virtual void process() = 0;

		//! returns event's type
		EventType get_type()const { return type; }

		//! change disable flag's value
		void set_disable(bool flag) { disable = flag; }
		
		//! check is disabled
		bool is_disabled() { return disable; }

		//! getter function for id field
		size_t get_id() { return id; }

		//! setter function for id field
		void set_id(size_t id) 
		{ 
			if (last_id >= id)
			{
				auto err = "Can't create event with id " + std::to_string(id) + " it must be higher than " + std::to_string(last_id);
				Goat2d::core::print_error(err);
				Goat2d::core::write_error(err);
				exit(-1);
			}
			this->id = id; 
			last_id = id;
		}


		//! clear static state. Call this function when scene is deleted
		static void clear_static_state()
		{
			object_counter = 0;
			last_id        = 0;
		}
	};

	//synonym to predicat that is used by KeyboardEvent class
	typedef std::function<bool(const SDL_Event& e)> keyboard_pred_t;

	/*!
	\brief This class represents every event connected to keyboard
	\author MAGANER
	\date 10.09.2023
	*/
	class KeyboardEvent :public BaseEvent<keyboard_pred_t, simple_callback_t>
	{	
	public:
		/*!
		\brief constructor for events working with outer state
		\param[in] pred lambda to check condition
		\param[in] fn action that must be executed if predicat returns true
		\param[in] state that can be used by predicat or action. It can't be nullptr, otherwise you should you another constructor
		*/
		KeyboardEvent(const keyboard_pred_t& pred, const simple_callback_t& fn, void* state):
			BaseEvent<keyboard_pred_t,simple_callback_t>(pred,fn,state,EventType::keyboard){}

		//constructor for events that can be described as pure functions
		//because they don't change/require any outer state, so state is just nullptr

		/*!
		\brief constructor for events without other state requirements
		\param[in] pred lambda to check condition
		\param[in] fn action that must be executed if predicat returns true
		*/
		KeyboardEvent(const keyboard_pred_t& pred, const simple_callback_t& fn):
			BaseEvent<keyboard_pred_t,simple_callback_t>(pred,fn,ZERO_STATE,EventType::keyboard){}
		~KeyboardEvent(){}

		//! process keyboard 
		void process(void* e)override
		{
			if (predicat(*static_cast<SDL_Event*>(e)))
				fn(state);
		}

		//isn't used
		[[deprecated]]
		void process()override { return; }
	};

	/*
	  This class represents common events of game.
	  However, it can be used to program anything that happens in game.
	*/

	/*!
	\brief This class represents common events of game. 
	\author MAGANER
	\date 10.09.2023
	*/
	class SimpleEvent : public BaseEvent<predicat_t, simple_callback_t>
	{
	private:
		//! some outer data passed to predicat. it can be nullptr
		void* predicat_event_to_check = nullptr; 
	public:

		//state and predicat_condition are variables
		//that a passed from another places.
		
		//most situation doesn't force you to pass
		//these arguments, so you can use second constructor

		/*!
		\brief creates event with outer data required by action and predicat
		\param[in] predicat lambda to check condition
		\param[in] fn action that must be executed if predicat returns true
		\param[in] type type of event
		\param[in] state data that is required by action
		\param[in] predicat_condition data that is required by predicat
		\warning most situation doesn't force you to pass special data for action and predicat, so it's better to use the second constructor
		*/
		SimpleEvent(const predicat_t& pred, 
					const simple_callback_t& fn, 
					EventType type, 
					void* state,
					void* predicat_condition):
			BaseEvent<predicat_t, simple_callback_t>(pred,fn,state,type)
		{
			predicat_event_to_check = predicat_condition;
		}

		/*!
		\brief constructor for events that doesn't require outer state to compute predicat value
		\param[in] predicat lambda to check condition
		\param[in] fn action that must be executed if predicat returns true
		\param[in] type type of event
		*/
		SimpleEvent(const predicat_t& pred,
					const simple_callback_t& fn,
					EventType type)
			:BaseEvent<predicat_t,simple_callback_t>(pred,fn,ZERO_STATE,type)
		{
			//predicat_event_to_check stay nullptr
		}
		~SimpleEvent(){}

		// process event depending on its type
		void process()override
		{
			if (type == EventType::nonconditional)
				fn(state);
			else
			{
				if (predicat(predicat_event_to_check))
					fn(state);
			}
		}
		
		//this function isn't used by this class
		[[deprecated]]
		void process(void* e)override { return; }
	};


//it's kinda strange trick
#define LAST_KEYBOARD_EVENT -3
#define LAST_NONCOND_EVENT  -2
#define LAST_COND_EVENT     -1


	/*!
	\brief class to sort and store events by their type
	\author MAGANER
	\date 10.09.2023
	*/
	class EventManager
	{
		std::list<KeyboardEvent*> keyboard_events;
		std::list<SimpleEvent*> nonconditional_events, conditional_events;
	public:
		EventManager(){}
		~EventManager()
		{
			if (!keyboard_events.empty())
				keyboard_events.front()->clear_static_state();

			if (!nonconditional_events.empty())
				nonconditional_events.front()->clear_static_state();

			if (!conditional_events.empty())
				conditional_events.front()->clear_static_state();
		}

		/*!
		\brief add KeyboardEvent to special list
		\param[in] event pointer to KeyboardEvent object
		*/
		void add_event(KeyboardEvent* event)
		{
			keyboard_events.push_back(event);
		}

		/*!
		\brief add SimpleEvent to special list
		\param[in] event pointer to SimpleEvent class
		*/
		void add_event(SimpleEvent* event)
		{
			if (event->get_type() == EventType::conditional)
				conditional_events.push_back(event);
			if (event->get_type() == EventType::nonconditional)
				nonconditional_events.push_back(event);
		}


		//! set disabling flag for all events
		void set_disable_for_all(bool flag)
		{
			for (auto& e : conditional_events)
				e->set_disable(flag);
			for (auto& e : nonconditional_events)
				e->set_disable(flag);
			for (auto& e : keyboard_events)
				e->set_disable(flag);
		}

		/*!
		\brief set disabling flag for all event, execpt the last special event
		\param[in] flag - true or flase
		\param[in] which_one - LAST_KEYBOARD_EVENT or LAST_NONCOND_EVENT or LAST_COND_EVENT
		*/
		void set_disable_for_all_execpt_last(bool flag, int which_one)
		{
			if (which_one == LAST_KEYBOARD_EVENT)
			{
				//exlude the last element
				for (auto it = keyboard_events.begin();
					it != --keyboard_events.end();
					++it)
					(*it)->set_disable(flag);

				for (auto& e : conditional_events)
					e->set_disable(flag);
				for (auto& e : nonconditional_events)
					e->set_disable(flag);
			}
			else if (which_one == LAST_NONCOND_EVENT)
			{
				//exlude the last element
				for (auto it = nonconditional_events.begin();
					it != --nonconditional_events.end();
					++it)
					(*it)->set_disable(flag);

				for (auto& e : conditional_events)
					e->set_disable(flag);
				for (auto& e : keyboard_events)
					e->set_disable(flag);
			}
			else if (which_one == LAST_COND_EVENT)
			{
				//exlude the last element
				for (auto it = conditional_events.begin();
					it != --conditional_events.end();
					++it)
					(*it)->set_disable(flag);

				for (auto& e : nonconditional_events)
					e->set_disable(flag);
				for (auto& e : keyboard_events)
					e->set_disable(flag);
			}
			else
			{
				Goat2d::core::print_error("Incorrect argument for set_disable_for_all_execpt_last()!\n");
				Goat2d::core::write_error("Incorrect argument for set_disable_for_all_execpt_last()!\n");
				return;
			}
		}


		/*!
		\brief set disabling flag for all event, execpt passed ids
		\param[in] flag - true or flase
		\param[in] l - initialiser list of ids
		*/
		void set_disable_for_all_execpt_special(bool flag, std::initializer_list<size_t> l)
		{
			for (auto& e : conditional_events)
				if(std::find(l.begin(),l.end(),e->get_id()) == l.end())
					e->set_disable(flag);
			for (auto& e : nonconditional_events)
				if (std::find(l.begin(), l.end(), e->get_id()) == l.end())
					e->set_disable(flag);
			for (auto& e : keyboard_events)
				if (std::find(l.begin(), l.end(), e->get_id()) == l.end())
					e->set_disable(flag);
		}

		//! get const reference to keyboard events list
		std::list<KeyboardEvent*>const & get_keyboard_events() const{ return keyboard_events; }

		//! get const reference to nonconditional events list
		std::list<SimpleEvent*> const & get_nonconditional_events() const { return nonconditional_events; }
		
		//! get const reference to conditional events list
		std::list<SimpleEvent*> const & get_conditional_events() const {return conditional_events; }
	};



	//use this functions in your keyboard predicats

	/*!
	\brief overwrapper function to be used in KeyboardEvent's predicats.
	\param[in] e SDL event that is used by KeyboardEvent object
	\param[in] key constant value that represents key
	*/
	static inline bool is_key_released(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYUP and e.key.keysym.sym == key;
	}

	/*!
	\brief overwrapper function to be used in KeyboardEvent's predicats.
	\param[in] e SDL event that is used by KeyboardEvent object
	\param[in] key constant value that represents key
	*/
	static inline bool is_key_pressed(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYDOWN and e.key.keysym.sym == key;
	}
};
};

#endif
#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include<list>
#include"SDL.h"
namespace Goat2d
{
namespace framework
{
	typedef std::function<bool(void* event)> predicat_t;
	typedef std::function<void(void* state)> simple_callback_t;

	enum class EventType:unsigned short
	{
		nonconditional,
		conditional,
		keyboard
	};

	//T is predicat class, F is action class E is class of event
	template<class T, class F>
	class BaseEvent
	{
	protected:
		T predicat;
		F fn;
		EventType type;

		void* state;
	public:
		BaseEvent(const T& predicat, 
				  const F& fn, 
				  void* state,
				  EventType type):predicat(predicat),fn(fn),state(state),type(type)
		{}
		virtual ~BaseEvent() {}

		virtual void process(void* event) = 0;
		virtual void process() = 0;

		EventType get_type()const { return type; }
	};

	typedef std::function<bool(const SDL_Event& e)> keyboard_pred_t;
	class KeyboardEvent :public BaseEvent<keyboard_pred_t, simple_callback_t>
	{	
	public:
		KeyboardEvent(const keyboard_pred_t& pred, const simple_callback_t& fn, void* state):
			BaseEvent<keyboard_pred_t,simple_callback_t>(pred,fn,state,EventType::keyboard){}
		~KeyboardEvent(){}
		void process(void* e)
		{
			if (predicat(*static_cast<SDL_Event*>(e)))
				fn(state);
		}
		void process() { return; }
	};
	class SimpleEvent : public BaseEvent<predicat_t, simple_callback_t>
	{
	public:
		SimpleEvent(const predicat_t& pred, const simple_callback_t& fn,void* state, EventType type):
			BaseEvent<predicat_t, simple_callback_t>(pred,fn,state,type){}
		~SimpleEvent(){}

		void process(void* e)
		{
			if (type == EventType::conditional)
				if (predicat(e))fn(state);
		}
		void process()
		{
			if (type == EventType::nonconditional)
				fn(state);
		}
	};

	class EventManager
	{
		std::list<KeyboardEvent*> keyboard_events;
		std::list<SimpleEvent*> nonconditional_events, conditional_events;
	public:
		EventManager(){}
		~EventManager(){}

		void add_event(KeyboardEvent* event)
		{
			keyboard_events.push_back(event);
		}
		void add_event(SimpleEvent* event)
		{
			if (event->get_type() == EventType::conditional)
				conditional_events.push_back(event);
			if (event->get_type() == EventType::nonconditional)
				nonconditional_events.push_back(event);
		}

		std::list<KeyboardEvent*>& get_keyboard_events(){ return keyboard_events; }
		std::list<SimpleEvent*>& get_nonconditional_events() { return nonconditional_events; }
		std::list<SimpleEvent*>& get_conditional_events() { return conditional_events; }
	};


	static inline bool is_key_released(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYUP and e.key.keysym.sym == key;
	}
	static inline bool is_key_pressed(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYDOWN and e.key.keysym.sym == key;
	}
};
};
#define ZERO_STATE (void*)nullptr
#endif
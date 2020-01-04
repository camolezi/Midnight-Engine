#ifndef EVENTDISPATCHER
#define EVENTDISPATCHER  

#include <functional>
#include <vector>
#include <unordered_map>
#include <queue>

#include <event.hpp>

namespace MN{

	class EventDispatcher{
		public:
			using memberPtr = std::function<void(Event::shared_ptr&)>;

			//Member Functions
			template<typename Function, typename Object>
			void subscribe(Event::EventType type,Function pointer, Object obj);

			//Regular functions
			template<typename Function>
			void subscribe(Event::EventType type,Function pointer);

			//Yet to implement
			void queueEvent(Event::unique_ptr& event);
			void fastEvent(Event::unique_ptr& event);

			static EventDispatcher& dispatcher();

			void update();
			void removeListener(memberPtr pointer);

		private:

			EventDispatcher(){};

			void addListener(const Event::EventType type, memberPtr pointer);

			// store a list of calls to functions, for every type of event 
			std::unordered_map<Event::EventType , std::vector<memberPtr> > callbacksMap;
			std::queue<Event::unique_ptr> eventQueue;

	};



	template<typename Function, typename Object>
	void EventDispatcher::subscribe(Event::EventType type,Function pointer, Object obj){
		std::function<void(Event::shared_ptr&)> handle_Ptr = std::bind( pointer, obj , std::placeholders::_1);
		this->addListener(type,handle_Ptr);
	}

	template<typename Function>
	void EventDispatcher::subscribe(Event::EventType type,Function pointer){
		std::function<void(Event::shared_ptr&)> handle_Ptr = pointer;
		this->addListener(type,handle_Ptr);
	}




}

#endif
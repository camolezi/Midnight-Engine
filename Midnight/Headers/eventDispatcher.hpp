#ifndef EVENTDISPATCHER
#define EVENTDISPATCHER  

#include <functional>
#include <vector>
#include <unordered_map>
#include <queue>

#include <event.hpp>

namespace MN{

	//For now all events are dispatched to all listenes (build a map later?) 
	class eventDispatcher{

		public:
			using memberPtr = std::function<void(Event::shared_ptr&)>;

			void addListener(const Event::EventType type, memberPtr pointer);

			//Yet to implement
			void removeListener(memberPtr pointer);
			void update();

			void fastEvent(Event::ptr& event);
			void queueEvent(Event::ptr& event);

		private:

			// store a list of calls to member functions, for every type of event 
			std::unordered_map<Event::EventType , std::vector<memberPtr> > callbacksMap;

			std::queue<Event::ptr> eventQueue;

	};
}

#endif
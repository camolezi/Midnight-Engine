#ifndef EVENTDISPATCHER
#define EVENTDISPATCHER  

#include <functional>
#include <vector>
#include <queue>

#include <event.hpp>

namespace MN{

	//For now all events are dispatched to all listenes (build a map later?) 
	class eventDispatcher{

		public:
			using memberPtr = std::function<void(Event::ptr)>;

			void addListener(memberPtr pointer);

			//Yet to implement
			void removeListener(memberPtr pointer);
			void update();

			void fastEvent(Event::ptr& event);
			void queueEvent(Event::ptr& event);

		private:

			//could be std::map<  , memberPtr>
			// // store a call to a member functions
			std::vector<memberPtr> callbacks;	

			std::queue<Event::ptr> eventQueue;

	};
}

#endif
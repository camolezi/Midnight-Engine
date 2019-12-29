#ifndef EVENTDISPATCHER
#define EVENTDISPATCHER  

#include <functional>
#include <vector>
#include <queue>
#include <memory>
#include <event.hpp>



 // store a call to a member function and object ptr
//	using std::placeholders::_1;
   // f_add_display3(3);


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
		std::vector<memberPtr> callbacks;

		std::queue<Event::ptr> eventQueue;

};


#endif
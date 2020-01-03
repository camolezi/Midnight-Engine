
#include <iostream>

#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>
#include <linuxWindow.hpp>

namespace MN{

	//Just for testing events right now
	class audioSystem{

	public:
		audioSystem(){

			EventDispatcher::dispatcher().subscribe(Event::EventType::message,&audioSystem::handleEvent,this);
			EventDispatcher::dispatcher().subscribe(Event::EventType::message,&audioSystem::handleEvent2,this);
		}

		void handleEvent(Event::pointer event){
			
			//Api for event handle
			auto test = downcast_event_ptr<MessageEvent>(event);
			TERMINAL_DEBUG(test->getMessage() << " In function 1");
		}

		void handleEvent2(Event::pointer event){

			auto test = downcast_event_ptr<MessageEvent>(event);
			TERMINAL_DEBUG(test->getMessage() << " In function 2");
		}

	};
}


//Just for testing Window closing event
bool run = true;
void windowShouldClose(MN::Event::pointer event){

	TERMINAL_DEBUG(event->getName());
	run = false;
}


int main(){


	using namespace MN;

	#ifdef debug
		std::cout << "Hello Debug Mode" << std::endl;
	#endif

	#ifdef deploy
		std::cout << "Hello deploy Mode" << std::endl;
	#endif


	TERMINAL_LOG_LEVEL(Log::Debug);
	TERMINAL_LOG(Log::Debug,"MidNight Engine - " << " :) ");


	Window::pointer windowPtr= Window::create();

	audioSystem audio;
	EventDispatcher::dispatcher().subscribe(Event::EventType::WindowCloseEvent,windowShouldClose);


	//Testing event API
	auto event = newEvent<MessageEvent>("My first message");
	EventDispatcher::dispatcher().queueEvent(event);


	event = newEvent<MessageEvent>();
	EventDispatcher::dispatcher().queueEvent(event);


	int x = 10000;
	while(run){
		EventDispatcher::dispatcher().update();
		windowPtr->update();
		Debug::TerminalLog::instance().flush();
	}

	return 0;
}
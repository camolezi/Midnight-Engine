
#include <iostream>

#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>
#include <linuxWindow.hpp>
#include <windowEvent.hpp>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

namespace MN{

	//Just for testing events in member functions right now
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

void windowResized(MN::Event::pointer event){

	using namespace MN;
	auto eventDownCast = downcast_event_ptr<WindowResizedEvent>(event);
	TERMINAL_DEBUG(eventDownCast->getName() << " Width" << 
			eventDownCast->getWidth() << " height" << eventDownCast->getHeight());
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
	EventDispatcher::dispatcher().subscribe(Event::EventType::WindowResizedEvent,windowResized);


	//Can subscribe with lambda expression
	auto printEvent = [](Event::pointer event){
		TERMINAL_DEBUG(event->to_string());
	};

	EventDispatcher::dispatcher().subscribe(Event::EventType::KeyPressedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::KeyReleasedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::MouseButtonPressedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::MouseButtonReleasedEvent,printEvent);

	//EventDispatcher::dispatcher().subscribe(Event::EventType::MouseMovedEvent,printEvent);

	while(run){
		EventDispatcher::dispatcher().update();
		windowPtr->update();
		Debug::TerminalLog::instance().flush();
		std::this_thread::sleep_for (std::chrono::milliseconds(50));
	}

	return 0;
}
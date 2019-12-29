
#include <iostream>
#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>

namespace MN{

	//Just for testing right now
	class audioSystem{

	public:
		audioSystem(eventDispatcher& disp){

			std::function<void(Event::ptr)> handle_Ptr = std::bind( &audioSystem::handleEvent, this , std::placeholders::_1);
			disp.addListener(handle_Ptr);
		}

		void handleEvent(Event::ptr event){
			
			std::unique_ptr<MessageEvent> test = downcast_event_ptr<MessageEvent>(event);
			std::cout << test->getMessage() << std::endl;
		}

	};

}




int main(){


	using namespace MN;

	#ifdef debug
		std::cout << "Hello Debug Mode" << std::endl;
	#endif

	Debug::TerminalLog logTest;

	logTest.write() << "My first Log";
	logTest.write() << "My second Log";


	eventDispatcher eventBus;
	audioSystem audio{eventBus};


	//Testing event API
	Event::ptr event = std::make_unique<MessageEvent>("Outra mesange");
	eventBus.queueEvent(event);


	event = std::make_unique<MessageEvent>("Mias Outra mesange");
	eventBus.queueEvent(event);


	bool run = true;
	while(run){
		eventBus.update();
		logTest.flush();
	}

	return 0;
}
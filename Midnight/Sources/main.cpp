
#include <iostream>
#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>

namespace MN{

	//Just for testing events right now
	class audioSystem{

	public:
		audioSystem(eventDispatcher& disp){

			std::function<void(Event::shared_ptr&)> handle_Ptr = std::bind( &audioSystem::handleEvent, this , std::placeholders::_1);
			std::function<void(Event::shared_ptr&)> handle_Ptr2 = std::bind( &audioSystem::handleEvent2, this , std::placeholders::_1);
			disp.addListener(Event::EventType::message,handle_Ptr);
			disp.addListener(Event::EventType::message,handle_Ptr2);
		}

		void handleEvent(Event::shared_ptr& event){
			
			std::shared_ptr<MessageEvent> test = downcast_event_ptr<MessageEvent>(event);
			TERMINAL_DEBUG(test->getMessage() << " In function 1");
		}

		void handleEvent2(Event::shared_ptr& event){

			std::shared_ptr<MessageEvent> test = downcast_event_ptr<MessageEvent>(event);
			TERMINAL_DEBUG(test->getMessage() << " In function 2");
		}

	};
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



	eventDispatcher eventBus;
	audioSystem audio{eventBus};


	//Testing event API
	Event::ptr event = std::make_unique<MessageEvent>("Outra mesange");
	eventBus.queueEvent(event);


	event = std::make_unique<MessageEvent>("Mias Outra mesange");
	eventBus.queueEvent(event);


	bool run = true;
	int x = 10000;
	while(run){
		eventBus.update();

		if(x < 0){
			run = false;
		}

		x--;
		//logTest.flush();
	}

	return 0;
}
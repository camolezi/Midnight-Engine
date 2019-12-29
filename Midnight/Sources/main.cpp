
#include <iostream>
#include <memory>
#include <event.hpp>
#include <eventDispatcher.hpp>


//Just for testing for now
class audioSystem{

public:
	audioSystem(eventDispatcher& disp){

		std::function<void(Event::ptr)> handle_Ptr = std::bind( &audioSystem::handleEvent, this , std::placeholders::_1);
		disp.addListener(handle_Ptr);
	}

	void handleEvent(Event::ptr event){
		
		std::unique_ptr<MessageEvent> teste = downcast_event_ptr<MessageEvent>(event);
		std::cout << teste->getMessage() << std::endl;
	}


};





int main(){

	std::cout << "Hello midNight" << std::endl;


	eventDispatcher eventBus;
	audioSystem audio{eventBus};


	//Testing event API
	Event::ptr event = std::make_unique<MessageEvent>("Outra mesange");
	eventBus.queueEvent(event);


	event = std::make_unique<MessageEvent>("Mias Outra mesange");
	eventBus.queueEvent(event);



	while(true){
		eventBus.update();
	}

	return 0;
}
#include <MidNight.hpp>

//Testing client application side

class clientApp : public MN::MidNightApp{

	public:	
		void run() override;
		~clientApp(){};
	private:
};

MN::MidNightApp * MN::MidNightApp::createApp(){
	return new clientApp;
}

void clientApp::run(){

	using namespace MN;
	//Can subscribe with lambda expression
	auto printEvent = [](Event::pointer event){
		TERMINAL_DEBUG(event->to_string());
	};
	EventDispatcher::dispatcher().subscribe(Event::EventType::KeyPressedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::KeyReleasedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::MouseButtonPressedEvent,printEvent);
	EventDispatcher::dispatcher().subscribe(Event::EventType::MouseButtonReleasedEvent,printEvent);

}


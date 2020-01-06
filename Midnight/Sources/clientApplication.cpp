#include <Midnight.hpp>

//Testing client application side

class clientApp : public MN::MidnightApp{

	public:	
		void run() override;
		~clientApp(){};
	private:
};

MN::MidnightApp * MN::MidnightApp::createApp(){
	return new clientApp;
}

void clientApp::run(){
	using namespace MN;

	//Testing client side API

	//Can subscribe with lambda expression or functions
	auto printEvent = [](MidnightEvent event){
	 	TERMINAL_DEBUG(event->to_string());
	};
	EventSubscribe(KeyPressedEvent,printEvent);
	EventSubscribe(KeyReleasedEvent,printEvent);


	//When ESC is pressed close the app
	EventSubscribe(KeyPressedEvent,[](MidnightEvent event){
		auto pressEvent = downcast_event_ptr<KeyPressedEvent>(event);
		if(pressEvent->pressed() == MN_KEY_ESCAPE){
			EventDispatche(newEvent<WindowCloseEvent>());
		} 
	});


}


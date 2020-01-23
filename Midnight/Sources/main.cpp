#include <iostream>

#include <eventDispatcher.hpp>
#include <debug.hpp>
#include <window.hpp>
#include <midnightApplication.hpp>
#include <coreMath.hpp>
#include <camera.hpp>
#include <input.hpp>
#include <renderer2D.hpp>
#include <eventMacro.hpp>

#include <time.hpp>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(){

	TERMINAL_LOG_LEVEL(Log::Debug);
	using namespace MN;

	#ifdef debug
		TERMINAL_LOG(Log::Debug,"Midnight Engine - Debug Mode  :) " );
	#endif

	#ifdef deploy
		//Remove 
		std::cout << "Hello deploy Mode" << std::endl;
	#endif

	Window::pointer windowPtr= Window::create();
	MN::Renderer2D::start();
	MN::Input::start();

	bool run = true;
	bool minimized = false;
	//Close window and end game engine
	EventDispatcher::dispatcher().subscribe(Event::EventType::WindowCloseEvent,[&run](Event::pointer event){
		TERMINAL_DEBUG("Closing Midnight");
		run = false;
	});

	EventSubscribe(WindowMinimizedEvent,[&minimized](MidnightEvent event){
		TERMINAL_DEBUG("Window Minimized");
		minimized = true;
	});

	EventSubscribe(WindowRestoredEvent,[&minimized](MidnightEvent event){
		TERMINAL_DEBUG("Window Restored");
		minimized = false;
	});


	//Create application
	MidnightApp * app = MidnightApp::createApp();
	ASSERT(app, "Failed to initialize application");
	app->start();


	Timer gameLoopTimer;
	double deltaTime = 0;
	while(run){

		gameLoopTimer.start();
		EventDispatcher::dispatcher().update();
		
		//Does not run app if window minimized
		if(!minimized)
	    	app->run(deltaTime);

		windowPtr->update();
		Debug::TerminalLog::instance().flush();
		std::this_thread::sleep_for (std::chrono::milliseconds(10));

		gameLoopTimer.stop();
		deltaTime = gameLoopTimer.getDuration();
	}


	delete app;
	return 0;
}


	// //Just for testing events in member functions right now
	// class audioSystem{

	// public:
	// 	audioSystem(){

	// 		EventDispatcher::dispatcher().subscribe(Event::EventType::message,&audioSystem::handleEvent,this);
	// 		EventDispatcher::dispatcher().subscribe(Event::EventType::message,&audioSystem::handleEvent2,this);
	// 	}

	// 	void handleEvent(Event::pointer event){
	// 		//Api for event handle
	// 		auto test = downcast_event_ptr<MessageEvent>(event);
	// 		TERMINAL_DEBUG(test->getMessage() << " In function 1");
	// 	}

	// 	void handleEvent2(Event::pointer event){

	// 		auto test = downcast_event_ptr<MessageEvent>(event);
	// 		TERMINAL_DEBUG(test->getMessage() << " In function 2");
	// 	}

	// };

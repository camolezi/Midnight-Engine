
#include <iostream>

#include <GLFW/glfw3.h>


#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>


namespace MN{

	//Just for testing events right now
	class audioSystem{

	public:
		audioSystem(EventDispatcher& disp){

			disp.subscribe(Event::EventType::message,&audioSystem::handleEvent,this);
			disp.subscribe(Event::EventType::message,&audioSystem::handleEvent2,this);
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




int main(){


	using namespace MN;

	#ifdef debug
		std::cout << "Hello Debug Mode" << std::endl;
	#endif

	#ifdef deploy
		std::cout << "Hello deploy Mode" << std::endl;
	#endif


	GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	




	TERMINAL_LOG_LEVEL(Log::Debug);
	TERMINAL_LOG(Log::Debug,"MidNight Engine - " << " :) ");


	

	EventDispatcher eventBus;
	audioSystem audio{eventBus};


	//Testing event API
	auto event = newEvent<MessageEvent>("My first message");
	eventBus.queueEvent(event);


	event = newEvent<MessageEvent>();
	eventBus.queueEvent(event);


	bool run = true;
	int x = 10000;
	while(run){
		eventBus.update();

		if(x < 0){
			run = false;
		}

		//x--;
		//logTest.flush();
	}

	glfwTerminate();
	return 0;
}
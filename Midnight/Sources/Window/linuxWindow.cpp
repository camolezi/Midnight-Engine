#include <linuxWindow.hpp>
#include <eventDispatcher.hpp>
#include <debug.hpp>
#include <windowEvent.hpp>
#include <inputEvent.hpp>

using namespace MN;

// window Factory
Window::pointer Window::create(const WindowData& data){
	//For now just return a linux window
 	return std::make_unique<LinuxWindow>(data);
}

	
//Initi glfw and setup callbacks
void LinuxWindow::init(){

	auto init = glfwInit();

	//Glfw Error callback
	glfwSetErrorCallback([](int error, const char* description){
		TERMINAL_LOG(Log::Error,description);
	});


	if (!init){
    // Initialization failed
		TERMINAL_LOG(Log::Error, "Failed to Initialize GLFW");
		ASSERT(init);
	}

	//Mininum open GL version required 
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	TERMINAL_DEBUG("Window width: " << data.width);
	TERMINAL_DEBUG("Window height: " << data.height);
	TERMINAL_DEBUG("Vsync: " << data.vsync);


	glfwWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (!glfwWindow){
    // Window or OpenGL context creation failed
		TERMINAL_LOG(Log::Error, "Failed to Initialize GLFW window or OpenGL context");
		ASSERT(glfwWindow);
	}

	glfwMakeContextCurrent(glfwWindow);

	//Set callBacks
	glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window){
		//Generate a window close Event
		auto event = newEvent<WindowCloseEvent>();
		EventDispatcher::dispatcher().queueEvent(event);
	});

	//Window resize event
	glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height){
		auto event = newEvent<WindowResizedEvent>(width, height);
		EventDispatcher::dispatcher().queueEvent(event);
	});


	glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xpos, double ypos){
		EventDispatcher::dispatcher().queueEvent(newEvent<MouseMovedEvent>(xpos,ypos));
	});


    //input Key press and release events
	glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods){
		switch(action){
			case(GLFW_PRESS):
				EventDispatcher::dispatcher().queueEvent(newEvent<KeyPressedEvent>(key));
				break;

			case(GLFW_RELEASE):
				EventDispatcher::dispatcher().queueEvent(newEvent<KeyReleasedEvent>(key));
				break;

			default:
				break;
		};
		
	});

	//Mouse	button event
	glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods){
		switch(action){
			case(GLFW_PRESS):
				EventDispatcher::dispatcher().queueEvent(newEvent<MouseButtonPressedEvent>(button));
				break;

			case(GLFW_RELEASE):
				EventDispatcher::dispatcher().queueEvent(newEvent<MouseButtonReleasedEvent>(button));
				break;

			default:
				break;
		};

	});

}


LinuxWindow::LinuxWindow(const WindowData& data){
	this->data = data;
	init();
}

LinuxWindow::~LinuxWindow(){
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


void LinuxWindow::update(){
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(glfwWindow);
    glfwPollEvents();

}



void LinuxWindow::setVSync(const bool vsy){ 

}


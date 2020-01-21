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

	
//Initi glfw, glad and setup callbacks
void LinuxWindow::initialize(){
	//Glfw Error callback
	glfwSetErrorCallback([](int error, const char* description){
		TERMINAL_LOG(Log::Error,description);
	});


	auto initGLFW = glfwInit();
	ASSERT(initGLFW, "Failed to Initialize GLFW");
	TERMINAL_DEBUG("Using GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	glfwWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	ASSERT(glfwWindow, "Failed to Initialize GLFW window or OpenGL context");

	TERMINAL_DEBUG("Window width: " << data.width);
	TERMINAL_DEBUG("Window height: " << data.height);
	TERMINAL_DEBUG("Vsync: " << data.vsync);

	glfwMakeContextCurrent(glfwWindow);

	auto gladInit = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(gladInit, "Failed to Initialize GLAD");

    TERMINAL_DEBUG("Using Glad-OpenGL Version: " << glGetString(GL_VERSION));
    TERMINAL_DEBUG("OpenGL Driver: " << glGetString(GL_RENDERER));

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

	glfwSetWindowIconifyCallback(glfwWindow, [](GLFWwindow* window, int iconified){
		if(iconified)
			EventDispatcher::dispatcher().queueEvent(newEvent<WindowMinimizedEvent>());
		else
			EventDispatcher::dispatcher().queueEvent(newEvent<WindowRestoredEvent>());
	});

	//Mouse moved envent
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

	//Icon
	// GLFWimage image;
	// image = load_icon("/home/Camolezi/Desktop/Midnight/Logos/logo.png"); 
	// glfwSetWindowIcon(glfwWindow, 1, &image);

}


LinuxWindow::LinuxWindow(const WindowData& data){
	this->data = data;
	initialize();
}

LinuxWindow::~LinuxWindow(){
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


void LinuxWindow::update(){
	glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
}



void LinuxWindow::setVSync(const bool vsy){ 

}


#include <linuxWindow.hpp>
#include <eventDispatcher.hpp>
#include <debug.hpp>
#include <windowEvent.hpp>

using namespace MN;

//Callbacks
static void window_close_callback(GLFWwindow* window);
static void window_size_callback(GLFWwindow* window, int width, int height);


// window Factory
Window::pointer Window::create(const WindowData& data){
	//For now just return a linux window
 	return std::make_unique<LinuxWindow>(data);
}

	

void LinuxWindow::init(){
	int init = glfwInit();
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
	glfwSetWindowCloseCallback(glfwWindow, window_close_callback);
	glfwSetWindowSizeCallback(glfwWindow, window_size_callback);


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



//GLFW callbacks
static void window_close_callback(GLFWwindow* window){
	//Generate a window close Event
	auto event = newEvent<WindowCloseEvent>();
	EventDispatcher::dispatcher().queueEvent(event);
}

static void window_size_callback(GLFWwindow* window, int width, int height){
	//Generate a window rezise envent
	auto event = newEvent<WindowResizedEvent>(width, height);
	EventDispatcher::dispatcher().queueEvent(event);
}



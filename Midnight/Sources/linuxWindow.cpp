#include <linuxWindow.hpp>
#include <terminalLog.hpp>


using namespace MN;

// window Factory
Window::pointer Window::create(const WindowData& data){
	//For now just return a linux window
 	return std::make_unique<LinuxWindow>(data);
}

	

void LinuxWindow::init(){
	if (!glfwInit()){
    // Initialization failed
		TERMINAL_LOG(Log::Error, "Failed to Initialize GLFW");
	}

	//Mininum open GL version required 
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


	glfwWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);
	if (!glfwWindow){
    // Window or OpenGL context creation failed
		TERMINAL_LOG(Log::Error, "Failed to Initialize GLFW window or OpenGL context");
	}

	glfwMakeContextCurrent(glfwWindow);


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

};

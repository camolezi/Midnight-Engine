#include <linuxWindow.hpp>
#include <eventDispatcher.hpp>
#include <debug.hpp>
#include <windowEvent.hpp>
#include <inputEvent.hpp>

//Iamgui test
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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

    glfwSwapInterval(0);
    //glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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


	//Just for testing iam gui 
	// move this from here
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

}


LinuxWindow::LinuxWindow(const WindowData& data){
	this->data = data;
	initialize();
}

LinuxWindow::~LinuxWindow(){
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}

static void iamguiTest() {

	static bool show_demo_window = true;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LinuxWindow::update(){
	iamguiTest();

	glfwSwapBuffers(glfwWindow);
   	glfwPollEvents();
}



void LinuxWindow::setVSync(const bool vsy){ 

}


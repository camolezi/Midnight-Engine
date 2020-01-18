#include <iostream>

#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>
//#include <linuxWindow.hpp>
#include <window.hpp>
#include <windowEvent.hpp>
#include <midnightApplication.hpp>
#include <coreMath.hpp>
#include <camera.hpp>

#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <shader.hpp>
#include <vertexArray.hpp>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include <renderer2D.hpp>


std::unique_ptr<MN::Shader> shaderProgram;
std::shared_ptr<MN::VertexArray> VAO;

//Just for testing draw a rectangule
static void renderTriangleTest(){
	using namespace MN;

	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec4 color;

		uniform mat4 scale = mat4(1);

		uniform mat4 viewProj = mat4(1);

		out vec4 fragColor;
		void main(){
			fragColor = color;
			gl_Position = viewProj * scale * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 finalColor;
		in vec4 fragColor;

		uniform vec4 uniformColor;
		void main(){
			finalColor = uniformColor;
		}
	)";

	shaderProgram = Shader::create(vertexShaderSource,fragmentShaderSource);
    float vertices[] = {
    	//Position  - color
         0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // top right
         0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };



    std::shared_ptr<VertexBuffer> VBO = VertexBuffer::create(sizeof(vertices), vertices);
    VBO->bind();

    std::shared_ptr<IndexBuffer> EBO = IndexBuffer::create(sizeof(indices), indices);
    EBO->bind();

    BufferLayout layout{
    	{ShaderDataType::FLOAT3, "Position"},
    	{ShaderDataType::FLOAT4, "Cor"}
    };

    VBO->setLayout(layout);

    VAO = VertexArray::create();
    VAO->setVertexBuffer(VBO);
    VAO->setIndexBuffer(EBO);

 }

//Just for testing the renderer
MN::OrthographicCamera camera(-10.0f,10.0f,10.0f,-10.0f,0.1f,20.0f);

static void render(){
	

    MN::Renderer2D::setClearColor({0.2f,0.3f,0.3f});
    MN::Renderer2D::clear();
    camera.setPosition({0,0,2.0f});

    mat4 scale = transform3D::translate(vec3{0.5f,0.1f,0.0f});

    shaderProgram->bind();
  	shaderProgram->uniformVec4("uniformColor",{1.0f,1.0f,0,1.0f});
  	shaderProgram->uniformMat4("scale", scale);
  	shaderProgram->uniformMat4("viewProj",camera.viewProjMatrix());


    MN::Renderer2D::drawQuad(VAO);
}

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

	bool run = true;
	//Close window and end game engine
	EventDispatcher::dispatcher().subscribe(Event::EventType::WindowCloseEvent,[&run](Event::pointer event){
		TERMINAL_DEBUG("Closing Midnight");
		run = false;
	});

	renderTriangleTest();

	//Create application
	MidnightApp * app = MidnightApp::createApp();
	ASSERT(app, "Failed to initialize application");
	app->start();


	while(run){
		EventDispatcher::dispatcher().update();
		windowPtr->update();

		render();
	    app->run();

		Debug::TerminalLog::instance().flush();
		std::this_thread::sleep_for (std::chrono::milliseconds(50));
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

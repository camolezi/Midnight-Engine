#include <iostream>

#include <event.hpp>
#include <eventDispatcher.hpp>
#include <terminalLog.hpp>
#include <linuxWindow.hpp>
#include <windowEvent.hpp>
#include <midnightApplication.hpp>
#include <coreMath.hpp>

#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <shaderOpenGL.hpp>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds



unsigned int VAO;

std::unique_ptr<MN::Shader> shaderProgram;

namespace MN{
	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type){
		switch(type){
			case ShaderDataType::FLOAT2: 
			case ShaderDataType::FLOAT3: 
			case ShaderDataType::FLOAT4: 
				return GL_FLOAT;
			default:
				ASSERT(false, "Invalid shader data type");
				return -1;
		};
	}

}

//Just for testing draw a rectangule
static void renderTriangleTest(){
	using namespace MN;

	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main(){
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main(){
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";

	shaderProgram = Shader::create(vertexShaderSource,fragmentShaderSource);
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);


    std::unique_ptr<VertexBuffer> VBO = VertexBuffer::create(sizeof(vertices), vertices);
    VBO->bind();

    std::unique_ptr<IndexBuffer> EBO = IndexBuffer::create(sizeof(indices), indices);
    EBO->bind();

    std::unique_ptr<BufferLayout> layout (new BufferLayout {
    	{ShaderDataType::FLOAT3, "Position"}
    });


    for(auto& element : (*layout) ){
    	glVertexAttribPointer(0, element.getCount(),
	    	ShaderDataTypeToOpenGL(ShaderDataType::FLOAT3),
	    	element.getNormalize(), 
	    	layout->getStride(), 
	    	(void*)element.getOffset());
    }


    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


 }

//Just for testing open gl
static void render(){
		//Just for now
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

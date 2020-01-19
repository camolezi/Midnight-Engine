#include <Midnight.hpp>

//Testing client application side

class clientApp : public MN::MidnightApp{

	public:	
		void run() override;
		void start() override;
		~clientApp(){};
	private:
		std::shared_ptr<MN::Camera> camera;
};

void clientApp::start(){
	//Testing client side API
	using namespace MN;
	
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
	//Camera
	camera = std::make_shared<OrthographicCamera>(-10.0f,10.0f,10.0f,-10.0f,0.1f,20.0f);
	MN::Renderer2D::setClearColor({0.2f,0.3f,0.3f});
}


void clientApp::run(){


	camera->setPosition({0,4.0f,2.0f});

	MN::Renderer2D::beginScene(camera);
    MN::Renderer2D::clear();
    //Render
    //MN::Renderer2D::drawQuad(MN::Transform2D{vec3{0,0,0}, 0, vec2{0,0} });

    MN::Renderer2D::drawQuad({ {5,5,0} , 30 , {1,6} } , {1.0f,0,0,1.0f}); //Red
    MN::Renderer2D::drawQuad({ {0,0,0} , -67 , {5,3} } , {0,1.0f,0,1.0f}); //Green
    MN::Renderer2D::drawQuad({ {-5,-5,0} , 0 , {2,1} } , {0,0,1.0f,1.0f});	//Blue


    MN::Renderer2D::endScene();

}


MN::MidnightApp * MN::MidnightApp::createApp(){
	return new clientApp;
}
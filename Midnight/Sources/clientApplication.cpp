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
	//When ESC is pressed close the app
	EventSubscribe(KeyPressedEvent,[](MidnightEvent event){
		auto pressEvent = downcast_event_ptr<KeyPressedEvent>(event);
		if(pressEvent->pressed() == MN_KEY_ESCAPE){
			EventDispatche(newEvent<WindowCloseEvent>());
		} 
	});
	//Camera
	camera = std::make_shared<OrthographicCamera>( -16.0f,16.0f,9.0f,-9.0f,0.1f,20.0f);
	MN::Renderer2D::setClearColor({0.2f,0.3f,0.3f});
}


void clientApp::run(){

	static float x = 0;
	static float y = 0;
	static float velocity = 0.3f;

	//Testing quad movment 
	if(MN::Input::isKeyPressed(MN_KEY_W)){
		y = y + velocity;
	}

	if(MN::Input::isKeyPressed(MN_KEY_S)){
		y = y - velocity;
	}

	if(MN::Input::isKeyPressed(MN_KEY_A)){
		x = x - velocity;
	}

	if(MN::Input::isKeyPressed(MN_KEY_D)){
		x = x + velocity;
	}

	camera->setPosition({0,4.0f,2.0f});

	MN::Renderer2D::beginScene(camera);
    MN::Renderer2D::clear();

    //Render
    //MN::Renderer2D::drawQuad(MN::Transform2D{vec3{0,0,0}, 0, vec2{0,0} });
    
    MN::Renderer2D::drawQuad({ {5,5,0} , 30 , {1,6} } , {1.0f,0,0,1.0f}); //Red
    MN::Renderer2D::drawQuad({ {-2,-3,0} , -67 , {5,3} } , {0,1.0f,0,1.0f}); //Green
    MN::Renderer2D::drawQuad({ {x,y,-1.0f} , 0 , {3,3} } , {0,0,1.0f,1.0f});	//Blue

    MN::Renderer2D::endScene();

}


MN::MidnightApp * MN::MidnightApp::createApp(){
	return new clientApp;
}
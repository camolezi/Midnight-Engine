#include <Midnight.hpp>

//Testing client application side	
class clientApp : public MN::MidnightApp{

	public:	
		void run(double deltaTime) override;
		void start() override;
		~clientApp(){};
	private:
		std::shared_ptr<MN::Camera> camera;
		std::shared_ptr<MN::Texture2D> texture;
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
	texture = Texture2D::create("../Midnight/Assets/Textures/midnightLogo.png");

	MN::Renderer2D::setClearColor({0.2f,0.3f,0.3f});
}


void clientApp::run(double deltaTime){

	static float x = 0;
	static float y = 0;
	float velocity = 7.0f * deltaTime;

	int mouseX = MN::Input::getMouseX();
	int mouseY = MN::Input::getMouseY();

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

	

	camera->setPosition({0,0,2.0f});

	MN::Renderer2D::beginScene(camera);
    MN::Renderer2D::clear();

    //Render
    //MN::Renderer2D::drawQuad(MN::Transform2D{vec3{0,0,0}, 0, vec2{0,0} });
	if (MN::Input::isMousePressed(MN_MOUSE_BUTTON_1)) {
		MN::Renderer2D::drawQuad({ {0,0,0.8f} , 0 , {1.5f,1.5f} }, { 1.0f,1.0f,0,1.0f });
	}


	MN::Renderer2D::drawQuad({ {0,0,-1} , 0 , {20,20} }, texture, { (x*x)/(16*10.0f),(y*y)/(9*5.0f),(x*y)/(10.0f*8.0f),1.0f}); //texture

    MN::Renderer2D::drawQuad({ { (((float)mouseX-1280.0f)/40.0f)+16, -((((float)mouseY-720.0f)/40.0f)+9),1.0f} , 0 , {0.6f,0.6f} } , {0.3f,1.0f,0.6f,1.0f});	//Blue
    MN::Renderer2D::drawQuad({ {x,y,0.5f} , 0 , {1.5f,1.5f} } , {0.0f,0,1,0.5f});

    MN::Renderer2D::endScene();

}


MN::MidnightApp * MN::MidnightApp::createApp(){
	return new clientApp;
}
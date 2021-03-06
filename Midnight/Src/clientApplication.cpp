#include <Midnight.hpp>

//Testing client application side	
class clientApp : public MN::MidnightApp{

	public:	
		void run(double deltaTime) override;
		void startApp() override;
		~clientApp(){};
	private:
		MN::Var<MN::Camera> camera;
		MN::Var<MN::Texture2D> texture;

		MN::Var<MN::Sound> testMusic;
		MN::Var<MN::Sound> testSound;

		MN::CountDownTimer timer = 4.0;

};

void clientApp::startApp(){
	//Testing client side API
	//Can subscribe with lambda expression or functions
	//When ESC is pressed close the app
	KeyPressedSubscribe([](MN::MidnightEvent event) {
		auto pressEvent = MN::downcast_event_ptr<MN::KeyPressedEvent>(event);
		if (pressEvent->pressed() == MN_KEY_ESCAPE) {
			EventDispatche(MN::newEvent<MN::WindowCloseEvent>());
		}
	});

	//New interface for subscribign in key press evetn
	SubscribeKeyPress(MN_KEY_M, []() {TERMINAL_DEBUG("Test"); });
	SubscribeLeftMouseClick([]() {TERMINAL_DEBUG("Test2"); } );


	//Testing sound API
	testSound = MN::Sound::createFromFile("../Midnight/Assets/Audio/sampleEffect.wav");
	testMusic = MN::Sound::createFromFile("../Midnight/Assets/Audio/sampleMusic.wav");
	testSound->setVolume(1.0f);

		
	//Camera
	camera = MN::Camera::createOrthographic(-16.0f,16.0f,9.0f,-9.0f,0.1f,20.0f);

	texture = MN::Texture2D::create("../Midnight/Assets/Textures/midnightLogo.png");

	MN::Renderer2D::setClearColor({0.8f,0.8f,0.8f});

}



void clientApp::run(double deltaTime){

	//sound Test
	using namespace MN;

	if (Input::isKeyPressed(MN_KEY_C)) {
		AudioEngine::playSoundLooped(testSound);
		AudioEngine::playSound(testMusic);
	}

	if (timer.countTime(deltaTime) == true) {
		//AudioEngine::playSoundLooped(testSound);
	}

	if (Input::isKeyPressed(MN_KEY_V)) {
		AudioEngine::stopSound(testSound);
	}

	if (Input::isKeyPressed(MN_KEY_P)) {
		AudioEngine::pauseSound(testSound);
	}


	//Render test

	static float x = 0;
	static float y = 0;
	float velocity = 7.0f * deltaTime;

	int mouseX = MN::Input::getMouseX();
	int mouseY = MN::Input::getMouseY();	

	/*
	//Transform 2D GUI test
	static float position[2] = { 0 ,0};
	static float rotation = 0.0f;
	static float color[4] = { 1.0f ,1.0f,1.0f,1.0f};
	static float depth = 0.5f;
	static bool win = true;
	if (win) {
		ImGui::Begin("Transform 2D", &win);
		ImGui::DragFloat2("Position", position);
		ImGui::DragFloat("Rotation", &rotation);
		ImGui::ColorEdit4 ("Color", color);
		ImGui::DragFloat("Depth", &depth);
		ImGui::End();
		ImGui::ShowTestWindow();
	}
	x = position[0];
	y = position[1];
	*/

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
	static Transform2D simpleObjectTransform;
	static vec4 simpleObjectcolor = 1.0f;
	MidnightWidget(simpleObjectTransform, simpleObjectcolor);
	//MN::Renderer2D::drawQuad(simpleObjectTransform, simpleObjectcolor);

	//x = simpleObjectTransform.Position.x();
	//y = simpleObjectTransform.Position.y();
    
    //MN::Renderer2D::drawQuad(MN::Transform2D{vec3{0,0,0}, 0, vec2{0,0} });
	if (MN::Input::isMousePressed(MN_MOUSE_BUTTON_1)) {
		//MN::Renderer2D::drawQuad({ {0,0,0.8f} , 0 , {1.5f,1.5f} }, { 1.0f,1.0f,0,1.0f });
	}

	//MN::Renderer2D::drawQuad({ {0,0,-1} , 0 , {20,20} }, texture, { 1.0f,1.0f,1.0f,1.0f}); //texture
  //  MN::Renderer2D::drawQuad({ { (((float)mouseX-1280.0f)/40.0f)+16, -((((float)mouseY-720.0f)/40.0f)+9),1.0f} , 0 , {0.6f,0.6f} } , {0.3f,1.0f,0.6f,1.0f});	//Blue


	//For testing batch renderer; Performance intensive task
	//The engine can now render 1000 quads per frame at a decent frame rate
	//Compare with bath renderer after implemented

	
	int numberOfRec = 0;
	for (int posx = -16; posx <= 16; posx++) {
		for (int posy = -9; posy <= 9; posy++) {

			for (int add = 1; add < 10; add++) {

				for (int add2 = 1; add2 < 10; add2++) {
					simpleObjectTransform.Position = { (float)posx + (add / 10.0f),(float)posy + (add2 / 10.0f),1.0f };
					MN::Renderer2D::drawQuad(simpleObjectTransform, simpleObjectcolor);
					numberOfRec++;

					simpleObjectTransform.Position = { (float)posx + (add2 / 10.0f),(float)posy + (add / 10.0f),1.0f };
					MN::Renderer2D::drawQuad(simpleObjectTransform, simpleObjectcolor);
					numberOfRec++;
				}
			}
		}
	}
	

	ImGui::Begin("FPS");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Number of quads: %d", numberOfRec);
	ImGui::End();



    MN::Renderer2D::endScene();

}


MN::MidnightApp * MN::MidnightApp::createApp(){
	return new clientApp;
}
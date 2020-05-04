# Midnight-Engine

![Midnight](Midnight/Assets/Promotional/midNightLogo840x840.png.png?raw=true "Midnight")

## Midnight

Midnight is a in development minimal game engine.

# Basic usage

## Graphics
 
 ```cpp

    //Create a camera on the start
    auto camera = std::make_shared<MN::OrthographicCamera>( -16.0f,16.0f,9.0f,-9.0f,0.1f,20.0f);

    //create a texture from a image at a path
    auto texture = MN::Texture2D::create("Assets/Textures/midnightLogo.png");


    .
    .
    .

    //On run


    camera->setPosition({0,0,2.0f});
    //BeginScene
    MN::Renderer2D::beginScene(camera);

    //Clear buffer
    MN::Renderer2D::setClearColor({0.8f,0.8f,0.8f});
    MN::Renderer2D::clear();

    MN::Transform2D simpleObjectTransform;
    simpleObjectTransform.Position = { posx,posy};
    simpleObjectTransform.Scale = { scalex,scaley};
    simpleObjectTransform.Rotation = -30;

	vec4 simpleObjectcolor = 1.0f;

    //Render a white quad at position posx,posy. Scaled by scalex and scaley. Rotated by -30.
    MN::Renderer2D::drawQuad(simpleObjectTransform, simpleObjectcolor);

    //Render a textured quad.
    MN::Renderer2D::drawQuad(simpleObjectTransform, texture);

    simpleObjectcolor = {1.0f,0,0,1.0f};
    //Render a red tinted textured quad
    MN::Renderer2D::drawQuad(simpleObjectTransform, texture, simpleObjectcolor);

    MN::Renderer2D::endScene();

 ```


## Sound
 
 ```cpp

    //On load
    auto effect = MN::Sound::createFromFile("Assets/Audio/effect.wav");
    auto music = MN::Sound::createFromFile("Midnight/Assets/Audio/music.wav");

    //half the original volume
    music->setVolume(0.5f);
    .
    .
    .

    //On run loop

    //Play looped
    MN::AudioEngine::playSoundLooped(music);

    if (MN::Input::isKeyPressed(MN_KEY_P)) {
        //Play a sound one time
		MN::AudioEngine::playSound(effect);
	}

    //Stop and reset the sound
	if (MN::Input::isKeyPressed(MN_KEY_S)) {
		AudioEngine::stopSound(effect);
	}

    //Pause, if played return in the point paused
	if (MN::Input::isKeyPressed(MN_KEY_P)) {
		AudioEngine::pauseSound(effect);
	}

 ```
 

## Input

 ```cpp

    //If the user hold 'P' the sound will be played in loop
    if (MN::Input::isKeyPressed(MN_KEY_P)) {
        //Play a sound one time
		MN::AudioEngine::playSound(effect);
	}

    //Mouse
    int mouseX = MN::Input::getMouseX();
	int mouseY = MN::Input::getMouseY();	

    //Mouse Click
    if (MN::Input::isMousePressed(MN_MOUSE_BUTTON_1)) {
		...
	}


    //----Input events
    
    //The argument is a function or lambda.
    SubscribeKeyPress(MN_KEY_M, []() {
        TERMINAL_DEBUG("M was pressed"); 
    });

	SubscribeLeftMouseClick([]() {TERMINAL_DEBUG("Left mouse was pressed"); } );


    //-------Timers

    static MN::CountDownTimer timer = 4.0;

    //Activate for one frame every 4 seconds.
    if (timer.countTime(deltaTime) == true) {
		//AudioEngine::playSoundLooped(testSound);
	}

 ```
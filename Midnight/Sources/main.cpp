#include <eventDispatcher.hpp>
#include <debug.hpp>
#include <window.hpp>
#include <midnightApplication.hpp>
#include <coreMath.hpp>
#include <camera.hpp>
#include <input.hpp>
#include <renderer2D.hpp>
#include <eventMacro.hpp>
#include <layer.hpp>
#include <time.hpp>
#include <audioEngine.hpp>
#include <uiLayer.hpp>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>        

#include <imgui.h>

//Testing github actions . V4

int main(){

	TERMINAL_LOG_LEVEL(Log::Debug);
	using namespace MN;

	#ifdef debug
		TERMINAL_LOG(Log::Debug,"Midnight Engine - Debug Mode  :) " );
	#endif

	#ifdef deploy
		//Remove 
		//std::cout << "Hello deploy Mode" << std::endl;
	#endif

	//Engine systems init
	//Window also create a open GL context, should be created before renderer and sound engine
	Window::pointer windowPtr= Window::create();
	MN::Renderer2D::start();
	MN::Input::start();
	MN::AudioEngine::start(windowPtr);

	bool run = true;
	bool minimized = false;
	//Close window and end game engine
	EventDispatcher::dispatcher().subscribe(Event::EventType::WindowCloseEvent,[&run](Event::pointer event){
		TERMINAL_DEBUG("Closing Midnight");
		run = false;
	});

	EventSubscribe(WindowMinimizedEvent,[&minimized](MidnightEvent event){
		TERMINAL_DEBUG("Window Minimized");
		minimized = true;
	});

	EventSubscribe(WindowRestoredEvent,[&minimized](MidnightEvent event){
		TERMINAL_DEBUG("Window Restored");
		minimized = false;
	});

	//Create engine layerStack
	LayerStack layerStack;

	//Create Layers
		//Application
	Layer::ptr applicationLayer(MidnightApp::createApp());
	layerStack.addLayer(applicationLayer);
		

	//Engine UI - will not be created in deploy
	#ifndef deploy
		Layer::ptr uiLayer = std::make_shared<UILayer>();
		layerStack.addLayer(uiLayer);
	#endif

	//Call start in all layers
	for (auto layer : layerStack) {
		layer->start();
	}

	Timer gameLoopTimer;
	double deltaTime = 1.0/60.0;
	CountDownTimer fps = 1.0f;
	int frameCount = 0;
	while(run){

		gameLoopTimer.start();
		EventDispatcher::dispatcher().update();

		//bool show_demo_window = true;
		//ImGui::ShowDemoWindow(&show_demo_window);

		if (!minimized) {
			//Update all layers in order, the first inserted is the first to be updated
			for (auto layer : layerStack) {
				layer->update(deltaTime);
			}
		}
		windowPtr->update();
		AudioEngine::update();
		//Flush Logs
		Debug::TerminalLog::instance().flush();
		//std::this_thread::sleep_for (std::chrono::milliseconds(10));
		
		gameLoopTimer.stop();
		frameCount++;
		deltaTime = gameLoopTimer.getDuration();
		if (fps.countTime(deltaTime) == true) {
			//std::cout << "\n FPS: " << frameCount;
			frameCount = 0;
		}

	}
	
	
	layerStack.clear();
	applicationLayer.reset();

	#ifndef deploy
		uiLayer.reset();
	#endif // !deploy

	AudioEngine::end();
	Renderer2D::end();
	windowPtr.reset();
	return 0;
}


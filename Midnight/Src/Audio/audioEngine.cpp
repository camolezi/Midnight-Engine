#include <audioEngine.hpp>

namespace MN {
	//Static variables
	std::unique_ptr<AudioEngineInterface> AudioEngine::audioEngine;

	void AudioEngine::start(Window::pointer win) {
		audioEngine = AudioEngineInterface::create();
		audioEngine->createContext(win);	
	}
	void AudioEngine::end() {
		audioEngine.release();
	}

	void AudioEngine::playSound(std::shared_ptr<Sound> sound) {
		audioEngine->playSound(sound);
	}

	void AudioEngine::update() {
		audioEngine->update();
	}

	void AudioEngine::stopSound(std::shared_ptr<Sound> sound) {
		audioEngine->stopSound(sound);
	}

	void AudioEngine::pauseSound(std::shared_ptr<Sound> sound){
		audioEngine->pauseSound(sound);
	}

	void AudioEngine::playSoundLooped(std::shared_ptr<Sound> sound){
		audioEngine->playSoundLooped(sound);
	}

	


}
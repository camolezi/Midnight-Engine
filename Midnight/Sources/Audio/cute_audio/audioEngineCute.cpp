
#include <audioEngineCute.hpp>
#include <debug.hpp>


namespace MN {

	std::unique_ptr<AudioEngineInterface> AudioEngineInterface::create() {
		return std::make_unique<AudioEngineCute>();
	}

	static inline cs_playing_sound_t * convertSoundFormat(void* data) {
		return static_cast<cs_playing_sound_t*>(data);
	}

	void AudioEngineCute::createContext(Window::pointer win) {
		//TODO:Make function to config this parameters
		ctx = cs_make_context(win->getNativeWindow(), 44100, 8192, 0, NULL);
		if (ctx == nullptr) {
			ASSERT(false, "Error in creating sound context");
		}
	}

	AudioEngineCute::AudioEngineCute() { ctx == nullptr; }

	AudioEngineCute::~AudioEngineCute() {
		cs_shutdown_context(ctx);
	}

	//Save or not save the file? Maybe exclude this function from API
	void AudioEngineCute::playSound(const std::string& path) {
		TERMINAL_DEBUG("Not yet supported, create a sound first");
	}

	void AudioEngineCute::playSound(std::shared_ptr<Sound> sound) {

		auto convertedSound = convertSoundFormat(sound->getSoundData());
	
		//Sound after a stop 
		if (convertedSound->loaded_sound == nullptr) {
			sound->reContext();
			cs_insert_sound(ctx, convertSoundFormat(sound->getSoundData()));
		}
		//Sound paused
		if (convertedSound->paused) {
			cs_pause_sound(convertedSound, 0);
		}
		else {
			//Normal insert, if sound is already inserted this function does nothing(based on tests);
			cs_insert_sound(ctx, convertedSound);
		}
		
	}

	void AudioEngineCute::stopSound(std::shared_ptr<Sound> sound) {
		auto convertedSound = convertSoundFormat(sound->getSoundData());
		if (cs_is_active(convertedSound) == 1) {
			cs_stop_sound(convertedSound);
			cs_loop_sound(convertedSound, 1);
		}else {
			TERMINAL_DEBUG("Trying to stop a sound that is not being played");
		}
	}

	void AudioEngineCute::pauseSound(std::shared_ptr<Sound> sound) {
		auto convertedSound = convertSoundFormat(sound->getSoundData());
		if (cs_is_active(convertedSound) == 1) {
			cs_pause_sound(convertedSound,1);
		}
		else {
			TERMINAL_DEBUG("Trying to pause a sound that is not being played");
		}
	}

	void AudioEngineCute::playSoundLooped(std::shared_ptr<Sound> sound){
		auto convertedSound = convertSoundFormat(sound->getSoundData());
		cs_loop_sound(convertedSound, 1);
		playSound(sound);
	}

	void AudioEngineCute::update() {
		//TODO: Move this to another thread. The sound API alredy has support, should be easy
		cs_mix(ctx);
	}

	
}
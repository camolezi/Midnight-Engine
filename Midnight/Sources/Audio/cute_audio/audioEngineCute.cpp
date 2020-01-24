
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
		ctx = cs_make_context(win->getNativeWindow(), 44100, 8192, 0, NULL);
	}

	AudioEngineCute::AudioEngineCute() {

	}
	AudioEngineCute::~AudioEngineCute() {
		cs_shutdown_context(ctx);
	}
	void AudioEngineCute::playSound(const std::string& path) {
		TERMINAL_DEBUG("Not yet supported, create a sound first");
	}

	void AudioEngineCute::playSound(std::shared_ptr<Sound> sound) {

		auto covertedSound = convertSoundFormat(sound->getSoundData());
		/*
		THis check is not working fow now. There is a ASSERT in the file load side
		if (covertedSound->loaded_sound->channels[0] != nullptr) {
			TERMINAL_LOG(Log::Warning, "Trying to play a sound no loaded, or missing a sound file");
			return;
		}
		*/
		cs_insert_sound(ctx, covertedSound);
		
	}

	void AudioEngineCute::update() {
		cs_mix(ctx);
	}

}

#include <audioEngineCute.hpp>
#include <debug.hpp>


namespace MN {

	std::unique_ptr<AudioEngineInterface> AudioEngineInterface::create() {
		return std::make_unique<AudioEngineCute>();
	}

	static inline cs_play_sound_def_t convertSoundFormat(void* data) {
		return (*static_cast<cs_play_sound_def_t*>(data));
	}

	void AudioEngineCute::createContext(Window::pointer win) {
		ctx = cs_make_context(win->getNativeWindow(), 44100, 8192, 10, NULL);
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
		 cs_play_sound(ctx, convertSoundFormat(sound->getSoundData()));
		 //cs_playing_sound_t* sound =
	}

	void AudioEngineCute::update() {
		cs_mix(ctx);
	}

}
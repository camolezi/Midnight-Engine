#ifndef SOUNDCUTE_SOUND
#define SOUNDCUTE_SOUND

#include <audioEngine.hpp>
#include <string>
#include <cute_sound.h>
#include <window.hpp>

namespace MN {

	class SoundCute{

	public:

		void loadSound(const std::string& path , Window::pointer windowPtr);

		SoundCute() = default;
		//SoundCute(const std::string& path) { loadSound(path); }

		void mix();

	private:
		cs_context_t* ctx;
		cs_loaded_sound_t audioFile;
		cs_play_sound_def_t def;
		cs_playing_sound_t* sound;
	};

}


#endif

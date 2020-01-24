#ifndef SOUNDCUTE_SOUND
#define SOUNDCUTE_SOUND

#include <audioEngine.hpp>
#include <string>
#include <cute_sound.h>


namespace MN {

	class SoundCute : public Sound{
	public:
		void loadSound(const std::string& path) override;
		SoundCute() = default;
		SoundCute(const std::string& path) { loadSound(path); }
		void* getSoundData() override;

		~SoundCute();
	private:
		cs_loaded_sound_t audioFile;
		cs_play_sound_def_t def;
		
	};

}


#endif

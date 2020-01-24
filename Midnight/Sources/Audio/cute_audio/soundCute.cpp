#include <soundCute.hpp>
#include <debug.hpp>


namespace MN {
	std::unique_ptr<Sound> Sound::createFromFile(const std::string& path) {
		return std::make_unique<SoundCute>(path);
	}

	void SoundCute::loadSound(const std::string& path) {

		audioFile = cs_load_wav(path.c_str());
		ASSERT(cs_error_reason == NULL, cs_error_reason << " in: " << path);
		
		def = cs_make_playing_sound(&audioFile);		
	}

	void* SoundCute::getSoundData() {
		return &def;
	}

	SoundCute::~SoundCute() {
		if (audioFile.playing_count == 0) {
			cs_free_sound(&audioFile);
		}
		else {
			TERMINAL_LOG(Log::Warning, "Trying to delete a sound file while it is still playing. File was not delete from memory");
		}	
	}

}
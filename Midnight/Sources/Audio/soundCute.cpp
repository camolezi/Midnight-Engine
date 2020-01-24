#include <soundCute.hpp>
#include <debug.hpp>


namespace MN {
	std::unique_ptr<Sound> Sound::createFromFile(const std::string& path) {
		return std::make_unique<SoundCute>(path);
	}

	void SoundCute::loadSound(const std::string& path) {

		audioFile = cs_load_wav(path.c_str());
		def = cs_make_def(&audioFile);
	}

	void* SoundCute::getSoundData() {
		return &def;
	}

	SoundCute::~SoundCute() {
		cs_free_sound(&audioFile);
	}
}
#include <soundCute.hpp>
#include <debug.hpp>


namespace MN {

	void SoundCute::loadSound(const std::string& path, Window::pointer windowPtr) {

	
		ctx = cs_make_context(windowPtr->getNativeWindow(), 44100, 8192, 10, NULL);
		
		audioFile = cs_load_wav(path.c_str());
		def = cs_make_def(&audioFile);
		sound = cs_play_sound(ctx, def);
		
		//cs_shutdown_context(ctx);
		//cs_free_sound(&audioFile);
	}

	void SoundCute::mix() {
		cs_mix(ctx);
	}
}
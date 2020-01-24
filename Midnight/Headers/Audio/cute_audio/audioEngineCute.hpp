#ifndef AUDIOCOMMANDCUTE_HPP
#define AUDIOCOMMANDCUTE_HPP

#include <cute_sound.h>
#include <memory>
#include <audioEngine.hpp>

namespace MN {
	
	class AudioEngineCute : public AudioEngineInterface{
	public:
		AudioEngineCute();
		~AudioEngineCute();
		void createContext(Window::pointer win) override;
		void playSound(const std::string& path) override;
		void playSound(std::shared_ptr<Sound> sound) override;

		void update() override;
	private:
		cs_context_t* ctx;
	};

}


#endif
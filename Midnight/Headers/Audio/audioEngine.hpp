#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include <string>
#include <memory>

namespace MN {

	class Sound {
		virtual void loadSound(const std::string& path) = 0;
		//virtual void play() = 0;
	};

	class AudioEngine {
	public:
		virtual ~AudioEngine() = default;
		virtual void playSound(const std::string& path) = 0;
		virtual void playSound(std::shared_ptr<Sound> sound) = 0;

	};
}


#endif
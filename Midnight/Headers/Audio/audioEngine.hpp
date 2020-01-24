#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include <string>
#include <memory>
#include <window.hpp>

namespace MN {

	class Sound {
	public:
		virtual void loadSound(const std::string& path) = 0;
		virtual void* getSoundData() = 0;

		static std::unique_ptr<Sound> createFromFile(const std::string& path);
	};

	class AudioEngineInterface {
	public:
		virtual ~AudioEngineInterface() = default;

		virtual void createContext(Window::pointer win) = 0;
		virtual void playSound(const std::string& path) = 0;
		virtual void playSound(std::shared_ptr<Sound> sound) = 0;
		virtual void update() = 0;

		static std::unique_ptr<AudioEngineInterface> create();
	};

	//Static wrapper
	class AudioEngine {
	public:
		static void start(Window::pointer win);
		static void end();
		static void playSound(std::shared_ptr<Sound> sound);

		//TODO
		//playSoundLoop
		//playSound (,Volume)
		//
		static void update();

	private:
		AudioEngine();
		static std::unique_ptr<AudioEngineInterface> audioEngine;
	};
}


#endif
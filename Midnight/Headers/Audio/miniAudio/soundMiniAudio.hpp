#ifndef AUDIOENGINEMINIAUDIO
#define AUDIOENGINEMINIAUDIO

#include <audioEngine.hpp>
#include <miniaudio.h>

namespace MN {

	class SoundMiniAudio : public Sound {
	public:
		SoundMiniAudio() = default;
		SoundMiniAudio(const std::string& path) { loadSound(path);}

		~SoundMiniAudio();

		void loadSound(const std::string& path) override;
		void play();

		static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
	private:
		ma_decoder decoder;
		ma_device_config deviceConfig;
		ma_device device;;

		bool playing = false;
		

		static ma_event g_stopEvent; /* <-- Signaled by the audio thread, waited on by the main thread. */
	};

}

#endif

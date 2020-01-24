#include <soundMiniAudio.hpp>
#include <debug.hpp>
#include <atomic>

namespace MN {

	std::atomic_bool finishPlaying = false;


	static void stop_callback(ma_device* pDevice) {
		finishPlaying = true;
	}

	void SoundMiniAudio::loadSound(const std::string& path) {
		
		ma_result result = ma_decoder_init_file(path.c_str(), NULL, &decoder);
		if (result != MA_SUCCESS) {
			TERMINAL_LOG(Log::Warning, "Audio file missing in: " << path);
		}

		deviceConfig = ma_device_config_init(ma_device_type_playback);

		deviceConfig.playback.format = decoder.outputFormat;
		deviceConfig.playback.channels = decoder.outputChannels;
		deviceConfig.sampleRate = decoder.outputSampleRate;
		deviceConfig.dataCallback = data_callback;
		deviceConfig.pUserData = &decoder;

		deviceConfig.stopCallback = stop_callback;

		if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
			ASSERT(false, "Error initializing the sound device");
			ma_decoder_uninit(&decoder);
		}

		//ma_event_init(device.pContext, &g_stopEvent);
	}
	void SoundMiniAudio::play() {


		if (finishPlaying) {
			playing = false;	
		}

		if (true) {
			TERMINAL_DEBUG("STARTING TO PLAY");
			
			if (ma_device_start(&device) != MA_SUCCESS) {
				ASSERT(false, "Error playing sound device: Maybe the device is already playing");
				ma_device_uninit(&device);
				ma_decoder_uninit(&decoder);
			}
			//ma_device_uninit(&device);
		//	ma_decoder_uninit(&decoder);
			playing = true;
		}
	}

	//running in audio thread
	void SoundMiniAudio::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{

		ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
		if (pDecoder == NULL) {
			ASSERT(false, "Error in soundEngine callback: Decoder is a nulltpr");
		}

		ma_uint64 framesRead = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);
		
		(void)pInput;
	}


	SoundMiniAudio::~SoundMiniAudio() {
		ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);
	}
}
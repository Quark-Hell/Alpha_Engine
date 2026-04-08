#include "SonarEngine/Resources/AudioClip.h"

#include "Core/Logger/Logger.h"

#include "SonarEngine/External/OpenAL/al.h"

namespace SonarEngine {

	AudioClip::AudioClip() {
		alGenBuffers(1, &_bufferID);

		Core::Logger::LogInfo("Audio Clip created");
	}

	AudioClip::~AudioClip() {
		if (_bufferID != 0) {
			alDeleteBuffers(1, &_bufferID);
		}

		Core::Logger::LogInfo("Audio Clip deleted");
	}

	void AudioClip::LoadMusic(const std::string& path) {

		std::string GlobalPath = path;

#ifdef WINDOWS
		std::replace(GlobalPath.begin(), GlobalPath.end(), '/', '\\');
#else
		std::replace(GlobalPath.begin(), GlobalPath.end(), '\\', '/');
#endif

		unsigned int channels;
		unsigned int sampleRate;
		uint64_t duration;

		int16_t* rawSamples = drwav_open_file_and_read_pcm_frames_s16(
			GlobalPath.data(),
			&channels,
			&sampleRate,
			&duration,
			nullptr
		);

		if (rawSamples == nullptr) {
			Core::Logger::LogError("Cannot load file. Samples info is null", __LOGERROR__);
			return;
		}

		_channels = channels;
		_sampleRate = sampleRate;
		_duration = duration;

		_samples.reset(rawSamples);
		ALenum format = (_channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

		alBufferData(
			_bufferID,
			format,
			_samples.get(),
			static_cast<ALsizei>(_duration * _channels * sizeof(int16_t)),
			_sampleRate
		);
	}

	unsigned int AudioClip::GetChannelsCount() const noexcept {
		return _channels;
	}

	unsigned int AudioClip::GetSampleRate() const noexcept {
		return _sampleRate;
	}

	unsigned int AudioClip::GetDuration() const noexcept {
		return _duration;
	}

	uint32_t AudioClip::GetOpenALBufferID() const noexcept {
		return _bufferID;
	}
}
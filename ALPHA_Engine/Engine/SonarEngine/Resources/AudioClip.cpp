#include "SonarEngine/Resources/AudioClip.h"

#include "Core/Logger/Logger.h"

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

	void AudioClip::LoadMusic() {
		_sampleRate = 22050;
		_duration = 2;
		_samples = _sampleRate * _duration;

		_data.clear();
		_data.reserve(_samples);

		for (int i = 0; i < _samples; i++) {
			_data.emplace_back(static_cast<short>(
				32760.f * sin((2.f * 3.1415926f * 440.f * i) / _sampleRate)
				));
		}

		alBufferData(
			_bufferID,
			AL_FORMAT_MONO16,
			_data.data(),
			static_cast<ALsizei>(_data.size() * sizeof(short)),
			_sampleRate
		);
	}

	int AudioClip::GetSampleRate() const noexcept {
		return _sampleRate;
	}

	int AudioClip::GetDuration() const noexcept {
		return _duration;
	}

	int AudioClip::GetSamples() const noexcept {
		return _samples;
	}

	ALuint AudioClip::GetOpenALBufferID() const noexcept {
		return _bufferID;
	}
}
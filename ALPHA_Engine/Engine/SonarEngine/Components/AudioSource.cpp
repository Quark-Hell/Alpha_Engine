#include "SonarEngine/Components/AudioSource.h"

#include "Core/Logger/Logger.h"

namespace SonarEngine {
	AudioSource::AudioSource() {
		Core::Logger::LogInfo("Audio Source created");

		alGenSources(1, &_bufferID);
	}

	AudioSource::~AudioSource() {
		if (_bufferID != 0) {
			alDeleteSources(1, &_bufferID);
		}
		Core::Logger::LogInfo("Audio Source deleted");
	}

	void AudioSource::SetAudioClip(AudioClip& audioClip) {
		_audioClip = &audioClip;

		alSourcei(_bufferID, AL_BUFFER, audioClip.GetOpenALBufferID());
	}

	void AudioSource::PlayMusic() {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
		}

		if (_audioClip == nullptr) {
			Core::Logger::LogError(
				"Audio Clip is null. Nothing to play. Try add audio clip using SetAudioClip() function",
				__LOGERROR__);
		}

		alSourcePlay(_bufferID);
	}

	void AudioSource::ClearAudioClip() noexcept {
		_audioClip = nullptr;
	}
	AudioClip* AudioSource::GetAudioClip() const noexcept {
		return _audioClip;
	}
}
#include "SonarEngine/Components/AudioSource.h"

#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"

#include <glm/gtc/type_ptr.hpp>

#include "SonarEngine/External/OpenAL/al.h"

namespace SonarEngine {
	AudioSource::AudioSource() {
		Core::Logger::LogInfo("Audio Source created");

		alGenSources(1, &_bufferID);

		SetGain(1.0f);
		SetPitch(1.0f);

		SetLooping(false);
		SetGlobal(false);

		SetReferenceDistance(10.0f);
		SetMaxDistance(100.0f);

		UpdatePosition();
	}

	AudioSource::~AudioSource() {
		if (_bufferID != 0) {
			alDeleteSources(1, &_bufferID);
		}
		Core::Logger::LogInfo("Audio Source deleted");
	}

	void AudioSource::UpdatePosition() {
		if (_bufferID == 0) {
			Core::Logger::LogError("Cannot update audio source position. Audio Source not inited", __LOGERROR__);
			return;
		}

		if (_parentObject == nullptr) {
			Core::Logger::LogError("Cannot update audio source position. Parent object is null", __LOGERROR__);
			return;
		}

		glm::vec3 position = _parentObject->transform.GetPosition();
		glm::vec3 linearVelocity = _parentObject->transform.GetLinearVelocity();

		alSourcefv(_bufferID, AL_POSITION, glm::value_ptr(position));
		alSourcefv(_bufferID, AL_VELOCITY, glm::value_ptr(linearVelocity));
	}

	void AudioSource::SetAudioClip(AudioClip& audioClip) {
		_audioClip = &audioClip;

		alSourcei(_bufferID, AL_BUFFER, audioClip.GetOpenALBufferID());
	}

	void AudioSource::Play() {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
		}

		if (_audioClip == nullptr) {
			Core::Logger::LogError(
				"Audio Clip is null. Nothing to play. Try add audio clip using SetAudioClip() function",
				__LOGERROR__);
		}

		_audioPlayStatus = AudioPlayStatus::Playing;
		alSourcePlay(_bufferID);
	}

	void AudioSource::Pause() {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
		}

		_audioPlayStatus = AudioPlayStatus::Pause;
		alSourcePause(_bufferID);
	}

	void AudioSource::Stop() {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
		}

		_audioPlayStatus = AudioPlayStatus::Chilling;
		alSourceStop(_bufferID);
	}

	void AudioSource::ClearAudioClip() noexcept {
		_audioClip = nullptr;
	}
	AudioClip* AudioSource::GetAudioClip() const noexcept {
		return _audioClip;
	}

	AudioPlayStatus AudioSource::GetPlayStatus() const noexcept {
		return _audioPlayStatus;
	}

	void AudioSource::SetGain(float gain) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		_gain = gain;
		alSourcef(_bufferID, AL_GAIN, _gain);
	}
	void AudioSource::SetPitch(float pitch) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		_pitch = pitch;
		alSourcef(_bufferID, AL_PITCH, _pitch);
	}
	void AudioSource::SetLooping(bool isLooping) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		_is_looping = isLooping;
		alSourcef(_bufferID, AL_LOOPING, _is_looping);
	}

	void AudioSource::SetGlobal(bool isGlobal) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		_isGlobal = isGlobal;

		if (_isGlobal) {
			alSourcei(_bufferID, AL_SOURCE_RELATIVE, AL_TRUE);
			alSourcef(_bufferID, AL_ROLLOFF_FACTOR, 0.0f);
		}
		else {
			alSourcei(_bufferID, AL_SOURCE_RELATIVE, AL_FALSE);
			alSourcef(_bufferID, AL_ROLLOFF_FACTOR, 1.0f);
		}
	}

	void AudioSource::SetReferenceDistance(float distance) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		if (distance < 0) {
			Core::Logger::LogError("reference distance cannot be less then zero", __LOGERROR__);
			return;
		}

		if (distance > _maxDistance) {
			Core::Logger::LogError("reference distance cannot be bigger then max distance", __LOGERROR__);
			return;
		}

		_referenceDistance = distance;
		alSourcef(_bufferID, AL_REFERENCE_DISTANCE, _referenceDistance);
	}
	void AudioSource::SetMaxDistance(float distance) {
		if (_bufferID == 0) {
			Core::Logger::LogError("Audio Source not inited", __LOGERROR__);
			return;
		}

		if (distance < 0) {
			Core::Logger::LogError("max distance cannot be less then zero", __LOGERROR__);
			return;
		}

		if (distance < _referenceDistance) {
			Core::Logger::LogError("max distance cannot be less then reference distance", __LOGERROR__);
			return;
		}

		_maxDistance = distance;
		alSourcef(_bufferID, AL_MAX_DISTANCE, _maxDistance);
	}
}
#pragma once

#include "Core/Components/Component.h"

#include "SonarEngine/Resources/AudioClip.h"

namespace SonarEngine {
	enum class AudioPlayStatus {
		Chilling,
		Pause,
		Playing,
	};
}

namespace SonarEngine {
	class AudioSource final : public Core::Component {
		friend class SonarEngine;
		friend class AudioSourcesBuffer;

	private:
		ALuint _bufferID = 0;
		AudioClip* _audioClip = nullptr;

		float _referenceDistance;
		float _maxDistance;

		float _gain;
		float _pitch;
		bool _is_looping;
		bool _isGlobal;

		AudioPlayStatus _audioPlayStatus;

	private:
		AudioSource();

		void UpdatePosition();

	public:
		void Play();
		void Pause();
		void Stop();


		void SetAudioClip(AudioClip& audioClip);

		[[nodiscard]] void ClearAudioClip() noexcept;
		[[nodiscard]] AudioClip* GetAudioClip() const noexcept;

		[[nodiscard]] AudioPlayStatus GetPlayStatus() const noexcept;

		void SetReferenceDistance(float distance);
		void SetMaxDistance(float distance);

		void SetGain(float gain);
		void SetPitch(float pitch);
		void SetLooping(bool isLooping);
		void SetGlobal(bool isGlobal);

		virtual ~AudioSource() override;
	};
}
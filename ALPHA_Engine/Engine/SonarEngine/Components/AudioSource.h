#pragma once

#include "Core/Components/Component.h"

#include "SonarEngine/Resources/AudioClip.h"

namespace SonarEngine {
	class AABB;

	class AudioSource final : public Core::Component {
		friend class SonarEngine;
		friend class AudioSourcesBuffer;

	private:
		ALuint _bufferID = 0;
		AudioClip* _audioClip = nullptr;

	private:
		AudioSource();

	public:
		void PlayMusic();
		void SetAudioClip(AudioClip& audioClip);

		[[nodiscard]] void ClearAudioClip() noexcept;
		[[nodiscard]] AudioClip* GetAudioClip() const noexcept;

		virtual ~AudioSource() override;
	};
}
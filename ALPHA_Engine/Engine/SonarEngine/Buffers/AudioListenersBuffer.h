#pragma once

#include "SonarEngine/Components/AudioListener.h"
#include "Core/ECS/TSystemData.h"

namespace SonarEngine {
	class AudioListenersBuffer final : public Core::TSystemData<AudioListener> {
		friend class SonarEngine;

	private:
		AudioListener* ActiveAudioListener = nullptr;

	public:
		AudioListenersBuffer(size_t initialBufferSize = 0);
		~AudioListenersBuffer() override = default;

		AudioListener& CreateAudioListener();
		void SetActiveAudioListener(AudioListener& listener);
	};
}
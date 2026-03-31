#pragma once

#include <vector>

#include "Core/Resources/Resource.h"

#include "AL/al.h"

namespace SonarEngine {
	class AudioClip : public Core::Resource {
		friend class Factory;

	private:
		ALuint _bufferID = 0;

		int _sampleRate = 0;
		int _duration = 0;
		int _samples = 0;

		std::vector<short> _data{};

	public:
		AudioClip();
		~AudioClip();

		void LoadMusic();

		[[nodiscard]] ALuint GetOpenALBufferID() const noexcept;

		[[nodiscard]] int GetSampleRate() const noexcept;
		[[nodiscard]] int GetDuration() const noexcept;
		[[nodiscard]] int GetSamples() const noexcept;
	};
}
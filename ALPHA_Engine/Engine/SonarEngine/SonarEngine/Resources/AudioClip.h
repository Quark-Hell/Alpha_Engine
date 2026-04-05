#pragma once

#include <memory>

#include "Core/Resources/Resource.h"
#include "SonarEngine/External/Dr_Libs/dr_wav.h"

namespace SonarEngine {
	struct DrWavDataDeleter {
		void operator()(int16_t* s) const noexcept {
			if (s) {
				drwav_free(s, nullptr);
			}
		}
	};
}

namespace SonarEngine {
	class AudioClip : public Core::Resource {
		friend class Factory;

	private:
		uint32_t _bufferID = 0;

		unsigned int _channels = 0;
		unsigned int _sampleRate = 0;
		uint64_t _duration = 0;
		std::unique_ptr<int16_t,DrWavDataDeleter> _samples = nullptr;

	public:
		AudioClip();
		~AudioClip();

		void LoadMusic(const std::string& path);

		[[nodiscard]] uint32_t GetOpenALBufferID() const noexcept;

		[[nodiscard]] unsigned int GetChannelsCount() const noexcept;
		[[nodiscard]] unsigned int GetSampleRate() const noexcept;
		[[nodiscard]] unsigned int GetDuration() const noexcept;
	};
}
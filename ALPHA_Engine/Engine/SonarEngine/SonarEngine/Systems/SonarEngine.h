#pragma once

#include <vector>
#include <memory>

#include "Core/ECS/System.h"

#include "SonarEngine/External/OpenAL/al.h"
#include "SonarEngine/External/OpenAL/alc.h"

#define DR_WAV_IMPLEMENTATION

namespace SonarEngine {
	struct ALCdeviceDeleter {
		void operator()(ALCdevice* s) const noexcept {
			if (s) alcCloseDevice(s);
		}
	};

	struct ALCcontextDeleter {
		void operator()(ALCcontext* s) const noexcept {
			if (s) {
				alcMakeContextCurrent(nullptr);
				alcDestroyContext(s);
			}
		}
	};
}

namespace SonarEngine {
	class SonarEngine final : public Core::System {

	private:
		std::unique_ptr<ALCdevice, ALCdeviceDeleter> device = nullptr;
		std::unique_ptr<ALCcontext, ALCcontextDeleter> context = nullptr;

		float _dopplerFactor;
		float _speedOfSound;

	private:
		void InitSonarEngine();

		void EntryPoint(std::vector<Core::SystemData*>& data) override;

	public:
		SonarEngine(size_t order);
		~SonarEngine() override = default;

		void SetDopplerFactor(float factor);
		void SetSpeedOfSound(float speed);

		[[nodiscard]] float GetDopplerFactor() const noexcept;
		[[nodiscard]] float GetSpeedOfSound() const noexcept;
	};
}
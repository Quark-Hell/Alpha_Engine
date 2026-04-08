#include "SonarEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Factory.h"
#include "Core/Logger/Logger.h"

#include "SonarEngine/Buffers/AudioSourcesBuffer.h"
#include "SonarEngine/Buffers/AudioListenersBuffer.h"

#include "SonarEngine/Components/AudioSource.h"
#include "SonarEngine/Resources/AudioClip.h"

namespace SonarEngine {
	SonarEngine::SonarEngine(size_t order) : System({ "AudioSourcesBuffer", "AudioListenersBuffer"}, order) {
		InitSonarEngine();

        SetDopplerFactor(0.0f);
        SetSpeedOfSound(343.3f);
	}

	void SonarEngine::InitSonarEngine() {
        device = std::unique_ptr<ALCdevice, ALCdeviceDeleter>(alcOpenDevice(nullptr));
        if (!device) {
            Core::Logger::LogCritical("Failed to open device", __LOGERROR__);
            return;
        }

        context = std::unique_ptr<ALCcontext, ALCcontextDeleter>(
            alcCreateContext(device.get(), nullptr)
        );
        if (!context) {
            Core::Logger::LogCritical("Failed to create context", __LOGERROR__);
            return;
        }
        alcMakeContextCurrent(context.get());
        alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	}

	void SonarEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
		if (data[0] == nullptr || data[1] == nullptr) {
			Core::Logger::LogError("Data was null: " + __LOGERROR__);
			return;
		}

		auto* audioSources = reinterpret_cast<AudioSourcesBuffer*>(data[0]);

        for (auto& source : audioSources->GetAllData()) {
            source->UpdatePosition();
        }

        auto* audioListeners = reinterpret_cast<AudioListenersBuffer*>(data[1]);
        for (auto& listener : audioListeners->GetAllData()) {
            listener->UpdateTransform();
        }
	}

    void SonarEngine::SetDopplerFactor(float factor) {
        if (factor < 0) {
            Core::Logger::LogError("Dopler factor cannot be less then zero", __LOGERROR__);
        }

        _dopplerFactor = factor;
        alDopplerFactor(_dopplerFactor);
    }
    void SonarEngine::SetSpeedOfSound(float speed) {
        if (speed < 0) {
            Core::Logger::LogError("Speed of sound cannot be less then zero", __LOGERROR__);
        }

        _speedOfSound = speed;
        alSpeedOfSound(_speedOfSound);
    }

    float SonarEngine::GetDopplerFactor() const noexcept {
        return _dopplerFactor;
    }
    float SonarEngine::GetSpeedOfSound() const noexcept {
        return _speedOfSound;
    }
}
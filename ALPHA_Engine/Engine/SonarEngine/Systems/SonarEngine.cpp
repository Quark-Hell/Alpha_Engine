#include "SonarEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Factory.h"
#include "Core/Logger/Logger.h"

#include "SonarEngine/Components/AudioSource.h"
#include "SonarEngine/Resources/AudioClip.h"

namespace SonarEngine {
	SonarEngine::SonarEngine(size_t order) : System({ }, order) {
		InitSonarEngine();
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
	}

	void SonarEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
		//if (data[0] == nullptr || data[1] == nullptr) {
		//	Core::Logger::LogError("Data was null: " + __LOGERROR__);
		//	return;
		//}

		//auto* audioSources = reinterpret_cast<CollidersBuffer*>(data[1]);
	}
}
#include "SonarEngine/Components/AudioListener.h"

#include "Core/Math/glmMath.h"
#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"

#include "AL/al.h"

#include <glm/gtc/type_ptr.hpp>

namespace SonarEngine {
	void AudioListener::UpdateTransform() {
		if (_isActive == false) {
			return;
		}

		if (_parentObject == nullptr) {
			Core::Logger::LogError("Cannot update audio listener Transform. Parent object is null",
				__LOGERROR__);

			return;
		}

		glm::vec3 position = _parentObject->transform.GetPosition();
		glm::vec3 linearVelocity = _parentObject->transform.GetLinearVelocity();

		glm::vec3 forward = _parentObject->transform.GetForward();
		glm::vec3 up = _parentObject->transform.GetUp();

		ALfloat orientation[6] = {
			forward.x, forward.y, forward.z,
			up.x, up.y, up.z
		};

		alListenerfv(AL_POSITION, glm::value_ptr(position));
		alListenerfv(AL_VELOCITY, glm::value_ptr(linearVelocity));
		alListenerfv(AL_ORIENTATION, orientation);
	}

	void AudioListener::SetActive(bool isActive) {
		_isActive = isActive;
	}

	bool AudioListener::GetIsActive() const noexcept {
		return _isActive;
	}
}
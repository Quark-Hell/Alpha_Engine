#pragma once

#include "Core/Components/Component.h"

namespace SonarEninge {
	class AudioListenersBuffer;
}

namespace SonarEngine {
	class AudioListener final : public Core::Component {
		friend class SonarEngine;
		friend class AudioListenersBuffer;

	private:
		bool _isActive = false;

	private:
		void UpdateTransform();
		void SetActive(bool isActive);

	public:
		[[nodiscard]] bool GetIsActive() const noexcept;
	};
}
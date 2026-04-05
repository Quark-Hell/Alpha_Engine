#pragma once

#include "Object.h"

namespace Core {
	class GameObject final : public Core::Object {
		friend class Factory;

	private:
		GameObject();

	public:
		~GameObject() override = default;
	};

}

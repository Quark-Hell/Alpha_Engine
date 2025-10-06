#pragma once

#include "Object.h"

namespace Core {
	class FakeObject final : public Core::Object {
		friend class Factory;

	private:
		FakeObject();

	public:
		~FakeObject() override = default;
	};
}
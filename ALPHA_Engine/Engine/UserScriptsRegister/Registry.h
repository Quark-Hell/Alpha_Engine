#pragma once
#include "Core/ECS/System.h"

namespace Register {
	class UserScript;

	class Registry final : public Core::System
	{
	public:
		Registry();
		~Registry() override = default;
		
	private:
		void EntryPoint(std::vector<Core::SystemData*>& data) override;
	};
}
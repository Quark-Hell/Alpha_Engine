#pragma once
#include "Core/ECS/System.h"

namespace Register {
	class UserScript;

	class Registry final : public Core::System
	{
	public:
		Registry();
		~Registry() override = default;

		static bool RegisterActorWithComponent(UserScript* script, const std::string &objectName = "Undefined");
		
	private:

		void EntryPoint(std::vector<Core::SystemData*>& data) override;
	};
}
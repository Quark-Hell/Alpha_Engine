#pragma once
#include "Core/ECS/System.h"

namespace Core {
	class Component;
}

namespace Register {
	class UserScript;

	class Registry final : public Core::System
	{
	public:
		static Registry* GetInstance();
		~Registry() override = default;

		static bool RegisterActorWithComponent(Register::UserScript* script, const std::string &objectName = "Undefined");
		
	private:
		Registry();
		void EntryPoint(Core::SystemData& data) override;
	};
}
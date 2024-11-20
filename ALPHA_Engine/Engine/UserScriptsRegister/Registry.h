#pragma once
#include "Core/ECS/System.h"

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

	//Registration system in World
	inline Register::Registry* userScriptSystem = Register::Registry::GetInstance();
}
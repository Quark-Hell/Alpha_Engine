#pragma once
#include "Core/ECS/System.h"

namespace Register {
	class UserScript;

	class Registry final : public Core::System
	{
	public:
		static Registry* GetInstance();
		~Registry() override = default;

		static bool RegisterActorWithComponent(UserScript* script, const std::string &objectName = "Undefined");
		
	private:
		Registry();
		void EntryPoint(std::vector<Core::SystemData*>& data) override;
	};

	//Registration system in World
	inline Registry* userScriptSystem = Registry::GetInstance();
}
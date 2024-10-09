#pragma once
#include "BaseConfig.h"

namespace Core {
	class Host;
}

namespace Register {
	class UserScript;

	class Registry
	{
		friend class Core::Host;

	private:
		static std::vector<std::shared_ptr<Register::UserScript>>& GetUserScripts();

	public:
		~Registry();

		static bool RegisterActorWithComponent(Register::UserScript* script, const std::string &objectName = "Undefined");
		static bool RegisterActor(const std::string& objectName = "Undefined");
		
	private:
		static std::unique_ptr<Register::Registry> MakeRegistry();
		Registry();

		//void RegistryStart();
		void RegistryLoop();
	};
}
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

	public:
		~Registry();

		static bool RegisterActorWithComponent(Register::UserScript* script, const std::string &objectName = "Undefined");
		
	private:
		static std::unique_ptr<Register::Registry> MakeRegistry();
		Registry();

		//void RegistryStart();
		void RegistryLoop(const std::list<std::unique_ptr<Register::UserScript>>* scripts);
	};
}
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

	public:
		~Registry();

		static bool RegisterActorWithComponent(Register::UserScript* script, const std::string &objectName = "Undefined");
		
	private:
		static Register::Registry& GetInstance();
		Registry();

		//void RegistryStart();
		void RegistryLoop(const std::list<std::unique_ptr<Register::UserScript>>* scripts);
	};
}
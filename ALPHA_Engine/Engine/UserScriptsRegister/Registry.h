#pragma once
#include "BaseConfig.h"

namespace Core {
	class Component;
	class Host;
}

namespace Register {
	class UserScript;

	class Registry
	{
		friend class Core::Host;

	public:
		~Registry() = default;

		static bool RegisterActorWithComponent(Register::UserScript* script, const std::string &objectName = "Undefined");
		
	private:
		static Register::Registry* GetInstance();
		Registry() = default;

		std::list<std::unique_ptr<Core::Component>>* _scripts;

		void LoadRegistryBuffer(std::list<std::unique_ptr<Core::Component>>* scripts);
		void RegistryLoop() const;
	};
}
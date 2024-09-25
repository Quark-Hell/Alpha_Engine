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
		std::vector<std::unique_ptr<Register::UserScript>> _userScripts;

	public:
		~Registry();

		bool RegisterScript(std::string path);

	private:
		static std::unique_ptr<Register::Registry> MakeRegistry();
		Registry();

		//void RegistryStart();
		void RegistryLoop();
	};
}


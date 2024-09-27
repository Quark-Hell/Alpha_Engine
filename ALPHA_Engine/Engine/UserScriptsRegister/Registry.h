#pragma once
#include "BaseConfig.h"

#ifdef ALPHA_Engine
#define ALPHA_ENGINE_API __declspec(dllexport)
#else
#define ALPHA_ENGINE_API __declspec(dllimport)
#endif

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

		bool RegisterActorWithComponent(Register::UserScript* script, std::string objectName = "Undefined");
		static bool RegisterActor(std::string objectName = "Undefined");
		
	private:
		static std::unique_ptr<Register::Registry> MakeRegistry();
		Registry();

		//void RegistryStart();
		void RegistryLoop();
	};
}


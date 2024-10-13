#pragma once
#include <Anomaly/WinManager/Window.h>

#include "BaseConfig.h"

namespace Core {
	class World;
}

namespace AnomalyEngine {
	namespace WindowsManager {
		class WindowsManager;
	}
}
namespace Register {
	class Registry;
	class UserScript;
}

namespace Core {

	class Host
	{
		friend class Core::World;

	private:
#if USER_SCRIPTS_REGISTER_INCLUDED
		std::unique_ptr<Register::Registry> _registry;
#endif

	private:
		static Host* GetInstance();
		Host();

	public:
		~Host();

#if USER_SCRIPTS_REGISTER_INCLUDED
		void Registry(const std::list<std::unique_ptr<Register::UserScript>>* scripts);
#endif

		void Graphics(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows);
		void Physics();
	};

}

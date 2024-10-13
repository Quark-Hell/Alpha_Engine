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
		static Host* GetInstance();
		Host();

	public:
		~Host();

	private:
#if USER_SCRIPTS_REGISTER_INCLUDED
		void Registry(const std::list<std::unique_ptr<Register::UserScript>>* scripts);
#endif

#if ANOMALY_ENGINE_INCLUDED
		void Graphics(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows);
#endif
		void Physics();
	};

}

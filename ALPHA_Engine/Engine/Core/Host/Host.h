#pragma once
#include "BaseConfig.h"

namespace Core {
	class World;
}

namespace Render {

	namespace WindowsManager {
		class WindowsManager;
		class Window;
	}

	namespace AnomalyEngine::Components {
		class Mesh;
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
		void InitRender();
		void LoadMeshData(std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* meshBuffer);
		void Graphics(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows);
#endif
		void Physics();
	};

}

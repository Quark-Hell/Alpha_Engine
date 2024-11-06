#pragma once
#include "BaseConfig.h"

namespace Render::WindowsManager::BindsEngine {
	class Bind;
}

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

#if RENDER_INCLUDED
		void InitRender();
		void RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows);
#endif

#if ANOMALY_ENGINE_INCLUDED
		void LoadMeshData(std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* meshBuffer);
#endif

#if BINDS_ENGINE_INCLUDED
		void LoadBindsBuffer(std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* binds);
#endif
		void Physics();
	};

}

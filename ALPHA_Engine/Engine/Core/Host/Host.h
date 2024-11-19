#pragma once
#include "BaseConfig.h"

namespace Render::WindowsManager::BindsEngine {
	class Bind;
}

namespace Core {
	class Component;
	class World;
}

namespace Render::WindowsManager {
	class WindowsManager;
	class Window;
}

namespace Core {
	class Geometry;

	class Host
	{
		friend class Core::World;

	private:
		static Host* GetInstance();
		Host();

	public:
		~Host();

	private:
		void LoadRegistryBuffer(std::vector<std::unique_ptr<Core::Component>> *scripts);
		void RegistryLoop();

		void InitRender();
		void RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows);

		void LoadMeshBuffer(std::vector<std::unique_ptr<Core::Component>>* meshBuffer);

		void LoadBindsBuffer(std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* binds);
		void Physics();
	};

}

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
		void LoadRegistryBuffer(std::list<std::unique_ptr<Core::Component>> *scripts);
		void RegistryLoop();

		void InitRender();
		void RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows);

		void LoadMeshBuffer(std::list<std::unique_ptr<Core::Geometry>>* meshBuffer);

		void LoadBindsBuffer(std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* binds);
		void Physics();
	};

}

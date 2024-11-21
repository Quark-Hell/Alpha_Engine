#pragma once
#include "BaseConfig.h"
#include <memory>

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
		void LoadMeshBuffer(std::vector<std::unique_ptr<Core::Component>>* meshBuffer);
		void Physics();
	};

}

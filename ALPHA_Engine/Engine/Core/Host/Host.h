#pragma once
#include "BaseConfig.h"

namespace Core {
	class World;
}

namespace GraphicsEngine {
	class RenderCore;
}
namespace Register {
	class Registry;
}

namespace Core {

	class Host
	{
		friend class Core::World;

	private:
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
		std::unique_ptr<GraphicsEngine::RenderCore> _graphics_engine;
#endif

#if __has_include("UserScriptsRegister/UserScriptConfig.h")
		std::unique_ptr<Register::Registry> _registry;
#endif

	private:
		static std::unique_ptr<Host> MakeHost();
		Host();

	public:
		~Host();

		void StartRender();

		void Regestry();
		void Graphics();
		void Physics();
	};

}

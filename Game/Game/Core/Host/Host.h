#pragma once
#include "BaseConfig.h"
#include "EngineDefines.h"

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
#if GRAPHICS_ENGINE_INCLUDED
		std::unique_ptr<GraphicsEngine::RenderCore> _graphics_engine;
#endif

#if USER_SCRIPTS_REGISTER_INCLUDED
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

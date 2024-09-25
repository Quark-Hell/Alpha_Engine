#include "Host.h"
#include "EngineConfig.h"



std::unique_ptr<Core::Host> Core::Host::MakeHost() {
	return std::unique_ptr<Core::Host>(new Host());
}

Core::Host::Host()
{
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine = GraphicsEngine::RenderCore::MakeRenderCore();
#endif
#if __has_include("UserScriptsRegister/UserScriptConfig.h")
	_registry = Register::Registry::MakeRegistry();
#endif
}

Core::Host::~Host()
{
}

void Core::Host::Regestry() {
#if __has_include("UserScriptsRegister/UserScriptConfig.h")
	_registry->RegistryLoop();
#endif
}

void Core::Host::StartRender() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine->StartRender();
#endif
}

void Core::Host::Graphics() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine->RenderLoop();
#endif
}


void Core::Host::Physics() {

}
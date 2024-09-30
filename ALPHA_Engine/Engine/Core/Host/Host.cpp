#include "Host.h"
#include "EngineConfig.h"

std::unique_ptr<Core::Host> Core::Host::MakeHost() {
	return std::unique_ptr<Core::Host>(new Host());
}

Core::Host::Host()
{
#if GRAPHICS_ENGINE_INCLUDED
	_graphics_engine = GraphicsEngine::RenderCore::MakeRenderCore();
#endif

#if USER_SCRIPTS_REGISTER_INCLUDED
	_registry = Register::Registry::MakeRegistry();
#endif
}

Core::Host::~Host()
{
}

void Core::Host::Regestry() {
#if USER_SCRIPTS_REGISTER_INCLUDED
	_registry->RegistryLoop();
#endif
}

void Core::Host::StartRender() {
#if GRAPHICS_ENGINE_INCLUDED
	_graphics_engine->StartRender();
#endif
}

void Core::Host::Graphics() {
#if GRAPHICS_ENGINE_INCLUDED
	_graphics_engine->RenderLoop();
#endif
}


void Core::Host::Physics() {

}
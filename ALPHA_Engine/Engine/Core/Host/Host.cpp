#include "Host.h"
#include "EngineConfig.h"


std::unique_ptr<Host> Host::MakeHost() {
	return std::unique_ptr<Host>(new Host());
}

Host::Host()
{
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine = Graphics_Engine::MakeGraphics_Engine();
#endif
}

Host::~Host()
{
}

void Host::StartRender() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine->StartRender();
#endif
}

void Host::Graphics() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_graphics_engine->RenderLoop();
#endif
}


void Host::Physics() {

}
#include "Host.h"
#include "EngineConfig.h"

Core::Host* Core::Host::GetInstance() {
	return new Host();
}

Core::Host::Host() = default;
Core::Host::~Host() = default;

void Core::Host::Registry(const std::list<std::unique_ptr<Register::UserScript>>* scripts) {
#if USER_SCRIPTS_REGISTER_INCLUDED
	auto registry = Register::Registry::GetInstance();

	registry.RegistryLoop(scripts);
#endif
}

//#include "Anomaly/WinManager/AnomalyEngine/Render.h"
void Core::Host::Graphics(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows) {
#if ANOMALY_ENGINE_INCLUDED
	auto rend = AnomalyEngine::Render::Render::GetInstance();

	rend.RenderLoop(windows);
#endif
}


void Core::Host::Physics() {

}
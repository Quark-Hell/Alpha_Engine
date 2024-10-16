#include "Host.h"
#include "EngineConfig.h"

Core::Host* Core::Host::GetInstance() {
	static Host host;
	return &host;
}

Core::Host::Host() = default;
Core::Host::~Host() = default;

#if USER_SCRIPTS_REGISTER_INCLUDED
void Core::Host::Registry(const std::list<std::unique_ptr<Register::UserScript>>* scripts) {
	auto registry = Register::Registry::GetInstance();
	registry->RegistryLoop(scripts);
}
#endif

#if ANOMALY_ENGINE_INCLUDED
void Core::Host::InitRender() {
	auto winManager = AnomalyEngine::WindowsManager::WindowsManager::GetInstance();
	winManager->Init();
}


void Core::Host::Graphics(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows) {\
	auto rend = AnomalyEngine::Render::Render::GetInstance();
	rend->RenderLoop(windows);
}
#endif

void Core::Host::Physics() {

}
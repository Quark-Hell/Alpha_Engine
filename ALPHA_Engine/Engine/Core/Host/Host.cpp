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

#if RENDER_INCLUDED
void Core::Host::InitRender() {
	const auto winManager = Render::WindowsManager::WindowsManager::GetInstance();
	winManager->Init();
}

void Core::Host::RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows) {
	const auto winManager = Render::WindowsManager::WindowsManager::GetInstance();
	winManager->RenderLoop(windows);
}
#endif

#if ANOMALY_ENGINE_INCLUDED
void Core::Host::LoadMeshData(std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* meshBuffer) {
	auto rend = Render::AnomalyEngine::RenderEngine::GetInstance();
	rend->LoadMeshArray(meshBuffer);
}
#endif

void Core::Host::Physics() {

}
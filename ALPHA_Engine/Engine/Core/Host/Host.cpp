#include "Host.h"
#include "EngineConfig.h"

Core::Host* Core::Host::GetInstance() {
	static Host host;
	return &host;
}

Core::Host::Host() = default;
Core::Host::~Host() = default;

#if ANOMALY_ENGINE_INCLUDED
void Core::Host::LoadMeshBuffer(std::vector<std::unique_ptr<Core::Component>>* meshBuffer) {
	const auto rend = Render::WindowsManager::AnomalyEngine::RenderEngine::GetInstance();
	rend->LoadMeshArray(meshBuffer);
}
#else
void Core::Host::LoadMeshBuffer(std::vector<std::unique_ptr<Core::Geometry>>* meshBuffer) {}
#endif

#if BINDS_ENGINE_INCLUDED
void Core::Host::LoadBindsBuffer(std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* binds) {
	const auto bind = Render::WindowsManager::BindsEngine::InputSystem::GetInstance();
	bind->LoadBindsBuffer(binds);
}
#else
void Core::Host::LoadBindsBuffer(std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* binds) {}
#endif

void Core::Host::Physics() {

}
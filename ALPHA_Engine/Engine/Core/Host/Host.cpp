#include "Host.h"
#include "EngineConfig.h"

Core::Host* Core::Host::GetInstance() {
	static Host host;
	return &host;
}

Core::Host::Host() = default;
Core::Host::~Host() = default;

#if USER_SCRIPTS_REGISTER_INCLUDED
void Core::Host::LoadRegistryBuffer(std::vector<std::unique_ptr<Core::Component>> *scripts) {
	const auto registry = Register::Registry::GetInstance();
	registry->LoadRegistryBuffer(scripts);
}
void Core::Host::RegistryLoop() {
	const auto registry = Register::Registry::GetInstance();
	registry->RegistryLoop();
}
#else
void Core::Host::LoadRegistryBuffer(std::list<std::unique_ptr<Core::Component>> *scripts) {}
void Core::Host::RegistryLoop() {}
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
#else
void Core::Host::InitRender() {}
void Core::Host::RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows) {}
#endif

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
#include "World.h"
#include <memory>
#include "Host/Host.h"
#include "EngineConfig.h"
#include "Core/Object.h"
#include "Render/WinManager/Window.h"

Core::World::World() = default;
Core::World::~World() = default;

#pragma region ObjectManager
std::list<std::unique_ptr<Core::Object>>* Core::World::GetObjects() {
	static std::list<std::unique_ptr<Core::Object>> objects{};
	return &objects;
}
#pragma endregion

#if USER_SCRIPTS_REGISTER_INCLUDED
std::list<std::unique_ptr<Register::UserScript>>* Core::World::GetUserScripts() {
	static std::list<std::unique_ptr<Register::UserScript>> userScripts{};
	return &userScripts;
}
#endif

#if RENDER_INCLUDED
std::vector<std::unique_ptr<Render::WindowsManager::Window>>* Core::World::GetWindows() {
	static std::vector<std::unique_ptr<Render::WindowsManager::Window>> windows{};
	return &windows;
}
#endif

#if ANOMALY_ENGINE_INCLUDED
std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Camera>>* Core::World::GetCameras() {
	static std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Camera>> cameras{};
	return &cameras;
}
std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* Core::World::GetMeshes() {
	static std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>> meshes{};
	return &meshes;
}
#endif

#pragma region WorldFunctions
Core::World* Core::World::GetWorld() {
	static World world;
	return &world;
}

void Core::World::CloseGame() {
	IsCloseGame = true;
}

bool Core::World::GetStateOfGame() const {
	return IsCloseGame;
}

double Core::World::GetTimeLong() const {
	return World::_timeLong;
}
float Core::World::GetDeltaTime() const {
	return World::_deltaTime;
}

void Core::World::StartFrame() {
	//World::_startTime = std::chrono::high_resolution_clock::now();
}
void Core::World::EndFrame() {
	//World::_endTime = std::chrono::high_resolution_clock::now();
	//What? Why i should mult this by 0.000001f?
	//World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() * 0.000001f;
	//World::_timeLong += World::_deltaTime;
}

void Core::World::SetSimulationSpeed(float simSpeed) {
	if (simSpeed < 0) {
		World::SimulationSpeed = simSpeed;
	}
}

void Core::World::Simulation() {
#if RENDER_INCLUDED
	Host::GetInstance()->InitRender();
#endif

	while (IsCloseGame)
	{
#if USER_SCRIPTS_REGISTER_INCLUDED
		Host::GetInstance()->Registry(GetUserScripts());
#endif

#if ANOMALY_ENGINE_INCLUDED
		Host::GetInstance()->LoadMeshData(GetMeshes());
#endif

#if RENDER_INCLUDED
		Host::GetInstance()->RenderLoop(GetWindows());
#endif
		//_host->Physics();
	}
}
#pragma endregion

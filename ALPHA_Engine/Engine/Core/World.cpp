#include "World.h"
#include <memory>
#include "EngineConfig.h"

#include "Core/Components/Geometry.h"
#include "Core/Object.h"
#include "Host/Host.h"

Core::World::World() = default;
Core::World::~World() = default;

#pragma region ObjectManager
std::list<std::unique_ptr<Core::Object>>* Core::World::GetObjects() {
	static std::list<std::unique_ptr<Core::Object>> objects{};
	return &objects;
}
#pragma endregion

std::list<std::unique_ptr<Core::Component>>* Core::World::GetUserScripts() {
	static std::list<std::unique_ptr<Core::Component>> userScripts{};
	return &userScripts;
}

#if RENDER_INCLUDED
std::vector<std::unique_ptr<Render::WindowsManager::Window>>* Core::World::GetWindows() {
	static std::vector<std::unique_ptr<Render::WindowsManager::Window>> windows{};
	return &windows;
}
#endif

std::vector<std::unique_ptr<Core::Component>>* Core::World::GetCameras() {
	static std::vector<std::unique_ptr<Core::Component>> cameras{};
	return &cameras;
}
std::list<std::unique_ptr<Core::Geometry>>* Core::World::GetMeshes() {
	static std::list<std::unique_ptr<Core::Geometry>> meshes{};
	return &meshes;
}

std::vector<std::unique_ptr<Core::Component>>* Core::World::GetDirectLights() {
	static std::vector<std::unique_ptr<Core::Component>> directLights{};
	return &directLights;
}
const std::vector<std::unique_ptr<Core::Component>> *Core::World::GetDirLights() {
	return Core::World::GetDirectLights();
}


std::vector<std::unique_ptr<Core::Component>>* Core::World::GetSpotLights() {
	static std::vector<std::unique_ptr<Core::Component>> spotLights{};
	return &spotLights;
}
std::vector<std::unique_ptr<Core::Component>>* Core::World::GetAreaLights() {
	static std::vector<std::unique_ptr<Core::Component>> areaLights{};
	return &areaLights;
}

#if BINDS_ENGINE_INCLUDED
std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* Core::World::GetBinds() {
	static std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>> binds{};
	return &binds;
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

void Core::World::SetSimulationSpeed(const float simSpeed) {
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
		Host::GetInstance()->LoadRegistryBuffer(GetUserScripts());
		Host::GetInstance()->RegistryLoop();

		Host::GetInstance()->LoadMeshBuffer(GetMeshes());

#if BINDS_ENGINE_INCLUDED
		Host::GetInstance()->LoadBindsBuffer(GetBinds());
#endif

#if RENDER_INCLUDED
		Host::GetInstance()->RenderLoop(GetWindows());
#endif
		//_host->Physics();
	}
}
#pragma endregion

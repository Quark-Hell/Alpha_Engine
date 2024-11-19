#include "World.h"
#include <memory>
#include <Logger/Logger.h>

#include "EngineConfig.h"

#include "Core/Components/Geometry.h"
#include "Core/Object.h"
#include "Host/Host.h"

Core::World::World() = default;
Core::World::~World() = default;

#pragma region ObjectManager
std::vector<std::unique_ptr<Core::Object>>* Core::World::GetObjects() {
	static std::vector<std::unique_ptr<Core::Object>> objects{};
	objects.reserve(64);
	return &objects;
}
#pragma endregion

std::vector<std::unique_ptr<Core::Component>>* Core::World::GetUserScripts() {
	static std::vector<std::unique_ptr<Core::Component>> userScripts{};
	userScripts.reserve(64);
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
std::vector<std::unique_ptr<Core::Component>>* Core::World::GetMeshes() {
	static std::vector<std::unique_ptr<Core::Component>> meshes{};
	meshes.reserve(64);
	return &meshes;
}

std::vector<std::unique_ptr<Core::Component>>* Core::World::GetDirectLights() {
	static std::vector<std::unique_ptr<Core::Component>> directLights{};
	directLights.reserve(16);
	return &directLights;
}
const std::vector<std::unique_ptr<Core::Component>> *Core::World::GetDirectLightsVec() {
	return Core::World::GetDirectLights();
}


std::vector<std::unique_ptr<Core::Component>>* Core::World::GetSpotLights() {
	static std::vector<std::unique_ptr<Core::Component>> spotLights{};
	spotLights.reserve(16);
	return &spotLights;
}
std::vector<std::unique_ptr<Core::Component>>* Core::World::GetPointLights() {
	static std::vector<std::unique_ptr<Core::Component>> areaLights{};
	areaLights.reserve(16);
	return &areaLights;
}
const std::vector<std::unique_ptr<Core::Component>>* Core::World::GetPointLightsVec() {
	return Core::World::GetPointLights();
}

#if BINDS_ENGINE_INCLUDED
std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* Core::World::GetBinds() {
	static std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>> binds{};
	binds.reserve(32);
	return &binds;
}
#endif


#pragma region WorldFunctions
Core::World* Core::World::GetWorld() {
	static World world;
	return &world;
}

void Core::World::CloseGame() {
	const auto world = GetWorld();
	world->_isCloseGame = true;
}

bool Core::World::GetStateOfGame() {
	const auto world = GetWorld();
	return world->_isCloseGame;
}

double Core::World::GetElapsedTime() {
	const auto world = GetWorld();
	return world->_timeElapsed;
}
double Core::World::GetDeltaTime() {
	const auto world = GetWorld();
	return world->_deltaTime;
}

void Core::World::SetSimulationSpeed(const float simSpeed) {
	if (simSpeed < 0) {
		const auto world = GetWorld();
		world->_simulationSpeed = simSpeed;
	}
}

float Core::World::GetWorldAmbient() {
	const auto world = GetWorld();
	return world->_worldAmbient;
}
void Core::World::SetWorldAmbient(const float ambient) {
	if (ambient < 0) {
		Logger::Logger::LogError("Ambient should be bigger than zero " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
		return;
	}
	const auto world = GetWorld();
	world->_worldAmbient = ambient;
}

void Core::World::Simulation() {
#if RENDER_INCLUDED
	Host::GetInstance()->InitRender();
#endif

	while (_isCloseGame)
	{
		_timer.Reset();

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

		_deltaTime = _timer.Elapsed();
		_timeElapsed += _timer.Elapsed();
		_timer.Reset();
	}
}
#pragma endregion

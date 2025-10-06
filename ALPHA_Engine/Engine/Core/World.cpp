#include "World.h"

#include "Core/Logger/Logger.h"
#include "Core/Objects/GameObject.h"
#include "Core/Objects/FakeObject.h"

namespace Core {
	Core::World::World() = default;
	Core::World::~World() = default;

	std::vector<std::unique_ptr<Core::GameObject>>* World::GetObjects() {
		static std::vector<std::unique_ptr<Core::GameObject>> objects{};
		objects.reserve(64);
		return &objects;
	}

	std::vector<std::unique_ptr<Core::FakeObject>>* World::GetFakeObjects() {
		static std::vector<std::unique_ptr<Core::FakeObject>> objects{};
		objects.reserve(64);
		return &objects;
	}

	void World::AddSystem(size_t order, Core::System* system) {
		if (system == nullptr) {
			Logger::LogError("System is null");
			return;
		}

		const auto world = World::GetWorld();
		world->_worldSystem.emplace(order, std::unique_ptr<Core::System>(system));
	}

	void World::AddSystemData(const std::string& systemDataName, Core::SystemData* systemData) {
		if (systemData == nullptr) {
			Logger::LogError("System data is null");
			return;
		}
		if (systemDataName.empty()) {
			Logger::LogError("System data name is empty" + std::string(__FILE__ ":") + std::to_string(__LINE__));
			return;
		}

		const auto world = World::GetWorld();
		if (world->_worldData.find(systemDataName) != world->_worldData.end()) {
			Logger::LogCritical("System data with name:", systemDataName, "already exists");
		}

		world->_worldData.emplace(systemDataName, std::unique_ptr<Core::SystemData>(systemData));
	}

	Core::System* World::GetSystem(const size_t order) {
		const auto world = World::GetWorld();
		if (world->_worldSystem.find(order) != world->_worldSystem.end()) {
			return world->_worldSystem[order].get();
		}
		Logger::LogError("System not found: " + __LOGERROR__);
		return nullptr;
	}

	Core::SystemData* World::GetSystemData(const std::string& systemDataName) {
		const auto world = World::GetWorld();
		if (world->_worldData.find(systemDataName) != world->_worldData.end()) {
			return world->_worldData[systemDataName].get();
		}
		Logger::LogError("System data not found: " + __LOGERROR__);
		return nullptr;
	}

#pragma region WorldFunctions
	Core::World* World::GetWorld() {
		static World world;
		return &world;
	}

	void World::CloseGame() {
		const auto world = GetWorld();
		world->_isCloseGame = true;
	}

	bool World::GetStateOfGame() {
		const auto world = GetWorld();
		return world->_isCloseGame;
	}

	double World::GetElapsedTime() {
		const auto world = GetWorld();
		return world->_timeElapsed;
	}
	double World::GetDeltaTime() {
		const auto world = GetWorld();
		return world->_deltaTime;
	}

	void World::SetSimulationSpeed(const float simSpeed) {
		if (simSpeed < 0) {
			const auto world = GetWorld();
			world->_simulationSpeed = simSpeed;
		}
	}

	float World::GetWorldAmbient() {
		const auto world = GetWorld();
		return world->_worldAmbient;
	}
	void World::SetWorldAmbient(const float ambient) {
		if (ambient < 0) {
			Logger::LogError("Ambient should be bigger than zero " + __LOGERROR__);
			return;
		}
		const auto world = GetWorld();
		world->_worldAmbient = ambient;
	}

	void World::Simulation() {
		InstanceModule();

		while (!_isCloseGame)
		{
			_timer.Reset();

			for (auto& system : _worldSystem) {
				const auto& tokens = system.second->GetTokens();

				std::vector<SystemData*> dataVector;
				dataVector.reserve(tokens.size());

				for (auto& token : tokens) {
					const auto data = _worldData.find(token);
					if (data == _worldData.end()) {
						Logger::LogWarning("Data for system with order", system.first, "by token", token, "not found: " + __LOGERROR__);

						dataVector.push_back(nullptr);
					}
					else {
						dataVector.push_back(data->second.get());
					}
				}
				system.second->EntryPoint(dataVector);
			}

			_deltaTime = _timer.Elapsed();
			_timeElapsed += _timer.Elapsed();
			_timer.Reset();
		}
		Logger::LogInfo("See you next time");
	}
#pragma endregion
}

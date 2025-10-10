#pragma once
#include <memory>

#include "Timer.h"

#include "map"
#include "unordered_map"

#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"
#include "Core/ECS/System.h"
#include "Core/ECS/SystemData.h"

namespace Core {
	class GameObject;
	class FakeObject;

	class System;
	class SystemData;

	extern void InstanceModule();

	class World {
		friend class Factory;
		friend class System;
		friend class SystemData;

	private:
		bool _isCloseGame = false;
		double _timeElapsed = 0;
		double _deltaTime = 0;

		float _simulationSpeed = 1;
		float _worldAmbient = 0.1f;

		Timer _timer;

		std::map<size_t, std::unique_ptr<System>> _worldSystem{};
		std::unordered_map<std::string, std::unique_ptr<SystemData>> _worldData{};

	private:
		static void AddSystem(size_t order, System* system);
		static void AddSystemData(const std::string& systemDataName, SystemData* systemData);

	public:
		[[nodiscard]] static System* GetSystem(size_t order);

		template <typename T>
		requires std::derived_from <T, Core::SystemData>
		[[nodiscard]] static inline T* GetSystemData(const std::string& systemDataName) {
			const auto world = World::GetWorld();
			if (world->_worldData.find(systemDataName) != world->_worldData.end()) {
				T* data = static_cast<T*>(world->_worldData[systemDataName].get());
				return data;
			}
			Logger::LogError("System data not found: " + __LOGERROR__);
			return nullptr;
		}

	private:
		static std::vector<std::unique_ptr<Core::GameObject>>* GetGameObjects();
		static std::vector<std::unique_ptr<Core::FakeObject>>* GetFakeObjects();

	private:
		World();

	public:
		World(const World& obj) = delete;
		~World();

		template <typename T>
		requires std::derived_from<T, Object>
		static bool DeleteObject(T& object) {
			auto world = World::GetWorld();
			std::vector<std::unique_ptr<T>>* list = nullptr;

			if constexpr (std::is_same_v<T, GameObject>) {
				list = World::GetGameObjects();
			}
			else {
				list = World::GetFakeObjects();
			}

			if (!list) {
				Logger::LogError("Object list not found");
				return false;
			}

			auto it = std::find_if(list->begin(), list->end(), [&](const auto& ptr) {
				return ptr.get() == &object;
				});

			if (it != list->end()) {
				// Remove component relations
				for (auto* comp : (*it)->GetComponents()) {
					comp->RemoveParent(object);
				}

				list->erase(it);
				Logger::LogInfo("GameObject removed");
				return true;
			}

			Logger::LogError("GameObject does not exist");
			return false;
		}

		static World* GetWorld();

		[[nodiscard]] static double GetDeltaTime();
		[[nodiscard]] static double GetElapsedTime();

		[[nodiscard]] static bool GetStateOfGame();

		[[nodiscard]] static float GetWorldAmbient();
		static void SetWorldAmbient(float ambient);

		static void CloseGame();
		static void SetSimulationSpeed(float simSpeed);

		//TODO: Make it private
		void Simulation();
	};
}

#pragma once
#include <memory>

#include "Timer.h"

#include "map"
#include "unordered_map"

#include "Core/ECS/System.h"
#include "Core/ECS/SystemData.h"

namespace Core {
	class Object;
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
		[[nodiscard]] static SystemData* GetSystemData(const std::string& systemDataName);

	private:
		static std::vector<std::unique_ptr<Core::Object>>* GetObjects();

	private:
		World();

	public:
		World(const World& obj) = delete;
		~World();

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

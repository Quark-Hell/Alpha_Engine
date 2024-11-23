#pragma once
#include <memory>

#include "Timer.h"

#include "unordered_map"
#include "map"
#include "Components/Component.h"

#include "Core/ECS/System.h"
#include "Core/ECS/SystemData.h"

#if RENDER_INCLUDED
namespace Render::WindowsManager {
	class Window;
	namespace BindsEngine {
		class Bind;
	}
}
#endif

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
		bool _isCloseGame = true;
		double _timeElapsed = 0;
		double _deltaTime = 0;

		float _simulationSpeed = 1;
		float _worldAmbient = 0.1f;

		Core::Timer _timer;

		std::map<size_t, std::unique_ptr<Core::System>> _worldSystem{};
		std::unordered_map<std::string, std::unique_ptr<Core::SystemData>> _worldData{};

	private:
		static void AddSystem(size_t order, Core::System* system);
		static void AddSystemData(const std::string& systemDataName, Core::SystemData* systemData);

	public:
		[[nodiscard]] static System* GetSystem(size_t order);
		[[nodiscard]] static SystemData* GetSystemData(const std::string& systemDataName);

	private:
		static std::vector<std::unique_ptr<Core::Object>>* GetObjects();

#if RENDER_INCLUDED
		//TODO: change to native sata type
		static std::vector<std::unique_ptr<Render::WindowsManager::Window>>* GetWindows();
#endif

		static std::vector<std::unique_ptr<Core::Component>>* GetCameras();
		static std::vector<std::unique_ptr<Core::Component>>* GetMeshes();

		static std::vector<std::unique_ptr<Core::Component>>* GetDirectLights();
		static std::vector<std::unique_ptr<Core::Component>>* GetPointLights();
		static std::vector<std::unique_ptr<Core::Component>>* GetSpotLights();


	public:
		static const std::vector<std::unique_ptr<Core::Component>>* GetDirectLightsVec();
		static const std::vector<std::unique_ptr<Core::Component>>* GetPointLightsVec();

	private:
		World();

	public:
		World(const World& obj) = delete;
		~World();

		static Core::World* GetWorld();

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

#pragma once
#include "BaseConfig.h"
#include "Timer.h"

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
  	class Geometry;
	class Component;

	class World {
		friend class Factory;

	private:
		bool _isCloseGame = true;
		double _timeElapsed = 0;
		double _deltaTime = 0;

		float _simulationSpeed = 1;
		float _worldAmbient = 0.1f;

		Core::Timer _timer;

	private:
		static std::vector<std::unique_ptr<Core::Object>>* GetObjects();

		static std::vector<std::unique_ptr<Core::Component>>* GetUserScripts();

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
#if BINDS_ENGINE_INCLUDED
		//TODO: change to native sata type
		static std::vector<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* GetBinds();
#endif

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

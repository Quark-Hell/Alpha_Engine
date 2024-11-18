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

		Core::Timer _timer;

	private:
		static std::list<std::unique_ptr<Core::Object>>* GetObjects();

		static std::list<std::unique_ptr<Core::Component>>* GetUserScripts();

#if RENDER_INCLUDED
		//TODO: change to native sata type
		static std::vector<std::unique_ptr<Render::WindowsManager::Window>>* GetWindows();
#endif

		static std::vector<std::unique_ptr<Core::Component>>* GetCameras();
		static std::list<std::unique_ptr<Core::Geometry>>* GetMeshes();

		static std::vector<std::unique_ptr<Core::Component>>* GetDirectLights();
		static std::vector<std::unique_ptr<Core::Component>>* GetSpotLights();
		static std::vector<std::unique_ptr<Core::Component>>* GetAreaLights();

	public:
		static const std::vector<std::unique_ptr<Core::Component>> *GetDirLights();

	private:
#if BINDS_ENGINE_INCLUDED
		//TODO: change to native sata type
		static std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* GetBinds();
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

		static void CloseGame();
		static void SetSimulationSpeed(float simSpeed);

		//TODO: Make it private
		void Simulation();
	};
}

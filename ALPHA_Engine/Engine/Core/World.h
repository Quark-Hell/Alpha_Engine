#pragma once
#include "BaseConfig.h"

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
		bool IsCloseGame = true;
		double _timeLong = 0;
		float _deltaTime = 0;
		std::chrono::steady_clock::time_point _startTime;
		std::chrono::steady_clock::time_point _endTime;

		float SimulationSpeed = 1;

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

		void StartFrame();
		void EndFrame();

	public:
		World(const World& obj) = delete;
		~World();

		static Core::World* GetWorld();

		void CloseGame();
		[[nodiscard]] bool GetStateOfGame() const;

		[[nodiscard]] double GetTimeLong() const;
		[[nodiscard]] float GetDeltaTime() const;

		void SetSimulationSpeed(float simSpeed);

		//TODO: Make it private
		void Simulation();
	};
}

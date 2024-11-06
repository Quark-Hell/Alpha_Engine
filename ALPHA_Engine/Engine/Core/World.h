#pragma once
#include "BaseConfig.h"

#if USER_SCRIPTS_REGISTER_INCLUDED
  namespace Register {
  	class UserScript;
  }
#endif

#if RENDER_INCLUDED
namespace Render {
  	namespace WindowsManager {
  		class Window;
  		namespace BindsEngine {
  			class Bind;
  		}
  	}

  	namespace AnomalyEngine::Components {
  		class Camera;
  		class Mesh;
  	}
  }
#endif

#if ANOMALY_ENGINE_INCLUDED
namespace Render::AnomalyEngine::Components {
	class Camera;
	class Mesh;
}
#endif

namespace Core {
	class Object;
	class Host;

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

#if USER_SCRIPTS_REGISTER_INCLUDED
	private:
		static std::list<std::unique_ptr<Register::UserScript>>* GetUserScripts();
#endif

#if RENDER_INCLUDED
	private:
		static std::vector<std::unique_ptr<Render::WindowsManager::Window>>* GetWindows();
#endif

#if ANOMALY_ENGINE_INCLUDED
		static std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Camera>>* GetCameras();
		//TODO: change std::vector to std::list
		static std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* GetMeshes();
#endif

#if BINDS_ENGINE_INCLUDED
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

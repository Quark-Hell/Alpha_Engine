#pragma once
#include "BaseConfig.h"

#if USER_SCRIPTS_REGISTER_INCLUDED
  namespace Register {
  	class UserScript;
  }
#endif

#if ANOMALY_ENGINE_INCLUDED
	namespace AnomalyEngine::WindowsManager {
	  class Window;
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

#if USER_SCRIPTS_REGISTER_INCLUDED
	private:
		static std::list<std::unique_ptr<Register::UserScript>>* GetUserScripts();
#endif

#pragma region ObjectManager
	private:
		static std::list<std::unique_ptr<Core::Object>>* GetObjects();
#pragma endregion

#if ANOMALY_ENGINE_INCLUDED
		static std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* GetWindows();
#endif

	private:
		World();

		void StartFrame();
		void EndFrame();

	public:
		World(const World& obj) = delete;
		~World();

		static Core::World& GetWorld();

		void CloseGame();
		[[nodiscard]] bool GetStateOfGame() const;

		[[nodiscard]] double GetTimeLong() const;
		[[nodiscard]] float GetDeltaTime() const;

		void SetSimulationSpeed(float simSpeed);

		//TODO: Make it private
		void Simulation();
	};
}

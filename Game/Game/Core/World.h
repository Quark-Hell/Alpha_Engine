#pragma once
#include "BaseConfig.h"

namespace Core {
	class Host;
}


enum DebugRenderModes {
	LinesRender = 1 << 0,
	PointsRender = 1 << 1
};

namespace Core {

	class World {
	private:
		//static inline std::vector<Object*> ObjectsOnScene;
		//static inline std::vector<Collider*> CollidersOnScene;
		//static inline std::vector<Light*> LightsOnScene;

#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	//std::vector<std::unique_ptr<Camera>>_cameras;
#endif
		std::unique_ptr<Core::Host> _host;

		bool IsCloseGame = true;
		double _timeLong = 0;
		float _deltaTime = 0;
		std::chrono::steady_clock::time_point _startTime;
		std::chrono::steady_clock::time_point _endTime;

		float SimulationSpeed = 1;

	public:
		static inline bool DebugRenderEnabled = false;
		static inline DebugRenderModes DebugRenderMode;

	public:
		//TODO: Make constructor is private
		World(const World& obj) = delete;
		World();
		~World();

		static std::unique_ptr<Core::World> MakeWorld();

		void StartFrame();
		void EndFrame();

		void CloseGame();

		bool GetStateOfGame();

		double GetTimeLong();
		float GetDeltaTime();

		void SetSimulationSpeed(float simSpeed);

		void Simulation();
	};

}
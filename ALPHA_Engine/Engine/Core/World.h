#pragma once
#include "BaseConfig.h"

#if USER_SCRIPTS_REGISTER_INCLUDED
	namespace Register {
		class UserScript;
	}
#endif

enum DebugRenderModes {
	LinesRender = 1 << 0,
	PointsRender = 1 << 1
};

namespace Core {
	class Object;
	class Host;

	class World {
	private:
		//static inline std::vector<Collider*> CollidersOnScene;
		//static inline std::vector<Light*> LightsOnScene;

#if GRAPHICS_ENGINE_INCLUDED
	std::vector<std::unique_ptr<Camera>>_cameras;
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

#if USER_SCRIPTS_REGISTER_INCLUDED
	private:
		static std::list<std::unique_ptr<Register::UserScript>>* GetUserScripts();
	public:
		static bool RemoveUserScript(const Register::UserScript* object);
		static Register::UserScript& CreateUserScript();
		static Register::UserScript* CreateUserScript(Register::UserScript* script);
#endif

#pragma region ObjectManager
	private:
		static std::list<std::unique_ptr<Core::Object>>* GetObjects();
	public:
		static bool RemoveObject(const Core::Object* object);
		static Core::Object& CreateObject();
#pragma endregion

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

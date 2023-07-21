#pragma once
#include "Basical_Type.h"
#include "Object.h"

class Object;

static class World {

private:
	static inline std::vector<Object*> ObjectsOnScene;
	static inline bool IsCloseGame = false;

	static inline double _timeLong = 0;
	static inline float _deltaTime = 0;
	static inline std::chrono::steady_clock::time_point _startTime;
	static inline std::chrono::steady_clock::time_point _endTime;

	static inline float SimulationSpeed = 1;

public:
	static void BuildTransformationThread(const std::vector<Object*> objects);
	static void ApplyingSceneTransformation();

	static void StartFrame();
	static void EndFrame();

	static void CloseGame();
	/// <summary>
	/// Return bool IsCloseGame
	/// </summary>
	static bool GetStateOfGame();

	static double GetTimeLong();
	static float GetDeltaTime();

	static void SetSimulationSpeed(float SimSpeed);

private:
	friend class Render;
	friend class Collision;
	friend class Object;
	friend class Physics;
	friend class RigidBody;

	World();
};
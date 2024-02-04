#pragma once
#include "Basical_Type.h"
#include "Object.h"
#include "BVH_Tree.h"

class Object;
class Light;

enum DebugRenderModes {
	LinesRender = 1 << 0,
	PointsRender = 1 << 1
};

class World {
private:
	static inline std::vector<Object*> ObjectsOnScene;
	static inline std::vector<Collider*> CollidersOnScene;
	static inline std::vector<Light*> LightsOnScene;

	static inline bool IsCloseGame = false;

	static inline double _timeLong = 0;
	static inline float _deltaTime = 0;
	static inline std::chrono::steady_clock::time_point _startTime;
	static inline std::chrono::steady_clock::time_point _endTime;

	static inline float SimulationSpeed = 1;

	static inline std::shared_ptr<Node> RootBVHnode;

public:
	static inline float WorldAmbientStrength = 0.5f;
	static inline Vector3 DebugWireframeColor = Vector3{ 0.012, 1, 0.153 };
	static inline float DebugWireframThickness = 2;

public:
	///TODO: In next update debug render will not work in release build
	static inline bool DebugRenderEnabled = false;
	static inline DebugRenderModes DebugRenderMode;

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

	static void CreateWorldTree();
	static void FindNearestCollider(Leaf& leafBuffer, std::vector<Collider*>& objectsBuffer, float maxDistance = 300);
	static void CreateAABBvolume(Node& outputNode, std::vector<std::shared_ptr<Leaf>>& leafBuffer);

	//TODO: Create interface instead friend class
private:
	friend class Render;
	friend class Collision;
	friend class Object;
	friend class Physics;
	friend class RigidBody;
	friend class Collider;
	friend class Light;
	friend class ShaderProgram;

	World();
};
#pragma once

#include <vector>
#include <filesystem>
#include <string>  
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <queue>
#include <algorithm>

#include "Matrix.h"
#include "Alghoritms.h"

class Object;

class Module
{
private:
	std::string _name;
	Object* ParentObject = nullptr;

private:
	friend class Render;
	friend class Object;

public:
	void Rename(std::string name);
	std::string GetName();
	Object* GetParentObject();

private:
	virtual void Test();
};

class Object {

private:
	Vector3 Position{ 0,0,0 };
	Vector4 Rotation{ 0,0,0,1 };
	Vector3 Scale{ 1,1,1 };

	Matrix4x4 _transformMatrix = Matrix4x4();

	std::vector<Module*> Modules;

public:
	Object();
	~Object();

	Vector3 GetPosition();
	void AddPosition(float X, float Y, float Z);
	void AddPosition(Vector3 position);

	void SetPosition(float X, float Y, float Z);
	void SetPosition(Vector3 position);


	Vector3 GetRotation();
	void AddRotation(float X, float Y, float Z);
	void AddRotation(Vector3 rotation);

	void SetRotation(float X, float Y, float Z);
	void SetRotation(Vector3 rotation);


	Vector3 GetScale();
	void AddScale(float X, float Y, float Z);
	void AddScale(Vector3 scale);

	void SetScale(float X, float Y, float Z);
	void SetScale(Vector3 scale);

	/*SetPosition, SetRotation and SetScale functions only change matrix of _transformMatrix.
	So this function apply transformation to object and recalculate vertex relative position;
	*/
	void ApplyTransform();

	bool AddModule(class Module* some_module);

	bool DeleteModuleByName(std::string name);
	bool DeleteModuleByIndex(int index);

	Module* GetModuleByName(std::string name);
	Module* GetModuleByIndex(size_t index);

	int GetCountOfModules();

	void DeleteObject();
};


static class World {

private:
	static inline std::vector<Object*> ObjectsOnScene;
	static inline bool IsCloseGame = false;

	static inline float _deltaTime;
	static inline std::chrono::steady_clock::time_point _startTime;
	static inline std::chrono::steady_clock::time_point _endTime;

private:
	void StartFrame();
	void EndFrame();

public:
	static inline void CloseGame();
	/// <summary>
	/// Return bool IsCloseGame
	/// </summary>
	static inline bool GetStateOfGame();
	static inline float GetDeltaTime();

private:
	friend class Object;
	friend class Render;

	World();
};

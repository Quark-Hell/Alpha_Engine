#pragma once
#include "Basical_Type.h"
#include "Modules/Transform.h"

enum ModulesList;

class Module;
class Vector4;
class Vector3;

class Object : public Transform {
private:
	std::vector<std::shared_ptr<Module>> Modules;

private:
	friend class Geometry;

public:
	Object();
	~Object();

#pragma region Redifine from Transfom
	Vector3 GetPosition() override;
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	Vector3 GetRotation() override;
	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	Vector3 GetScale() override;
	void SetScale(float X, float Y, float Z) override;
	void SetScale(Vector3 scale) override;

	/*SetPosition, SetRotation and SetScale functions only change matrix of _transformMatrix.
	So this function apply transformation to object and recalculate vertex relative position;
	*/
	void ApplyTransformation() override;
#pragma endregion

	bool AddModule(std::shared_ptr<Module> someModule);
	bool AddModule(ModulesList moduleType, Module& outputModule);

	bool DeleteModuleByType(ModulesList type);
	bool DeleteModuleByIndex(int index);

	std::shared_ptr<Module> GetModuleByType(ModulesList type);
	std::vector<std::shared_ptr<Module>> GetModuleByTypes(std::vector<ModulesList> typesArray);
	std::shared_ptr<Module> GetModuleByIndex(size_t index);

	int GetCountOfModules();

	void DeleteObject();

	unsigned long GetGeometryHeaviness();
};
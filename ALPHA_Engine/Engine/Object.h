#pragma once
#include "Basical_Type.h"
#include "Modules/Transform.h"
#include "Modules/BoxCollider.h"

#include "AABB.h"

enum ModulesList;

class Module;
class Vector4;
class Vector3;

class Object : public Transform {
private:
	std::vector<std::shared_ptr<Module>> Modules = std::vector<std::shared_ptr<Module>>();

	//TODO: add interface for this class
	/////////////////////
	friend class Geometry;
	friend class Camera;
	/////////////////////

	friend class BoxCollider;
	friend class World;

public:
	Object();
	~Object();

#pragma region Redifine from Transfom
	Vector3 GetPosition() override;
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	Vector4 GetRotation() override;
	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	Vector3 GetScale() override;
	void SetScale(float X, float Y, float Z) override;
	void SetScale(Vector3 scale) override;

	Vector3 GetOriginPosition();

	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;
	
	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	/*SetPosition, SetRotation and SetScale functions only change matrix of _transformMatrix.
	So this function apply transformation to object and recalculate vertex relative position;
	*/
	void ApplyTransformation() override;
#pragma endregion

	bool AddModule(std::shared_ptr<Module> someModule);
	bool AddModule(ModulesList moduleType, Module** outputModule);
	bool AddModule(ModulesList moduleType);

	bool DeleteModuleByType(ModulesList type);
	bool DeleteModuleByIndex(int index);

	std::shared_ptr<Module> GetModuleByType(ModulesList type);
	std::vector<std::shared_ptr<Module>> GetModuleByTypes(std::vector<ModulesList> typesArray);
	std::shared_ptr<Module> GetModuleByIndex(size_t index);

	int GetCountOfModules();

	glm::mat4x4& GetTransformationMatrix();

	void DeleteObject();

	unsigned long GetGeometryHeaviness();
};
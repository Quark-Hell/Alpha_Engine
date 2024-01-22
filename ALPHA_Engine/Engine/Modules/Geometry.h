#pragma once
#include "Module.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Modules/MovableModule.h"

class Object;
class Mesh;

class Geometry : public virtual MovableModule {
protected:
	bool _isShifted = false;
	bool _isIndexed = false;

	Object* _parentObject;

	//std::shared_ptr<std::vector<float>> _vertex = std::make_shared<std::vector<float>>();
	//std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();
	float* _vertex;
	float* _normals;

	unsigned int _vertexCount = 0;
	unsigned int _normalsCount = 0;

	friend class Object;
	friend class Render;
	friend class Collision;
	friend class Physics;
	friend class RigidBody;

public:
	Geometry();
	~Geometry();

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

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

	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;

	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	void ApplyTransformation() override;
#pragma endregion

	ModulesList GetType() override;

	virtual bool Create(std::string linkToFBX);
	//virtual void Delete();

	virtual Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();
};
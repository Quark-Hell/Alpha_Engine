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

	std::shared_ptr<std::vector<float>> _vertex = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();
	//float* _vertex = nullptr;

	//unsigned int _vertexCount = 0;

	friend class Object;
	friend class Render;
	friend class Collision;
	friend class Physics;
	friend class RigidBody;
	friend class DebugMesh;

public:
	Geometry();
	~Geometry();

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

#pragma region Redifine from Transfom
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	void SetScale(float X, float Y, float Z) override;
	void SetScale(Vector3 scale) override;

	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;

	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	void ApplyTransformation() override;

	glm::mat4x4 GetTransformMatrix() override;
#pragma endregion

	ModulesList GetType() override;

	virtual bool Create(std::string linkToFBX);
	virtual bool Create(std::string linkToFBX, 
		bool initIndices = true, 
		bool initVertex = true, 
		bool initNormals = true,
		bool initTexCoord = false, 
		bool initMaterial = false);
	//virtual void Delete();

	//virtual bool SetVertices(float* vertices, float count);
	virtual bool InsertVertex(Vector3 vertex, unsigned int pos, bool expand = false);
	bool ShiftVertexArray(int shiftCount);

	virtual Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();
};
#pragma once
#include "Geometry.h"
#include "Modules/Material.h"

#include "Modules/Camera.h"

class Mesh : public Geometry {
protected:
	std::shared_ptr<std::vector<float>> _vertexColors = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<float>> _texCoords = std::make_shared<std::vector<float>>();

	unsigned int _vertexVbo = 0;
	unsigned int _colorsVbo = 0;
	unsigned int _normalsVbo = 0;
	unsigned int _texCoordsVbo = 0;
	unsigned int _vao = 0;

public:
	std::shared_ptr<Material> _material = std::make_shared<Material>();

public:
	Mesh();
	~Mesh();

	ModulesList GetType() override;

	void SetParentObject(const Object& parent) override;

	bool Create(std::string linkToFBX) override;
	bool Create(std::string linkToFBX, bool initIndices, bool initVertex, bool initNormals, bool initTexCoord, bool initMaterial) override;

	bool LoadTextureCoord(std::string pathToCoords);

	virtual bool BindMesh();

#pragma region Redifine from Transfom
protected:
	void ApplyTransformation() override;
#pragma endregion

protected:
	friend class Object;
	friend class Render;
	friend class MeshCollider;

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};
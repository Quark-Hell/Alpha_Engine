#pragma once
#include "Geometry.h"
#include "Modules/Material.h"

class Mesh : public Geometry {
private:
	friend class Object;
	friend class Render;

private:
	std::shared_ptr<Material> _material = std::make_shared<Material>();
	std::shared_ptr<std::vector<float>> _texCoords = std::make_shared<std::vector<float>>(std::vector<float>());
	std::shared_ptr<std::vector<float>> _vertexColors = std::make_shared<std::vector<float>>();

	unsigned int _vertexVbo = 0;
	unsigned int _colorsVbo = 0;
	unsigned int _vao = 0;

public:
	Mesh();
	~Mesh();

	ModulesList GetType() override;

	void SetParentObject(const Object& parent) override;

	bool Create(std::string linkToFBX) override;

	void ApplyTransformation() override;

	bool LoadTextureCoord(std::string pathToCoords);
	bool LoadTextureCoord(const aiScene& scene, unsigned int matIndex);

	bool BindMesh();

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};
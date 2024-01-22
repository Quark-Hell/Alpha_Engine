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
#pragma endregion

	bool LoadTextureCoord(std::string pathToCoords);
	bool LoadTextureCoord(const aiScene& scene, unsigned int matIndex);

	bool BindMesh();

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};
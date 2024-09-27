#pragma once
#include "Geometry.h"

namespace GraphicsEngine {
	class Material;

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

		bool InsertVertex(Vector3 vertex, unsigned int pos, bool expand = false) override;

		bool LoadTextureCoord(std::string pathToCoords);

		virtual bool BindMesh();
	};
}
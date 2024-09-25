#pragma once

#include "BaseConfig.h"
#include "Core/Modules/Module.h"

class Geometry : public Module
{
	friend class RenderCore;

protected:
	bool _isIndexed = false;

	std::shared_ptr<std::vector<float>> _vertex = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
	std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();

public:
	Geometry();
	~Geometry();

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

	ModulesList GetType() override;

	virtual bool Create(std::string linkToFBX);
	virtual bool Create(std::string linkToFBX,
		bool initIndices = true,
		bool initVertex = true,
		bool initNormals = true,
		bool initTexCoord = false,
		bool initMaterial = false);

	virtual bool InsertVertex(Vector3 vertex, unsigned int pos, bool expand = false);
	bool ShiftVertexArray(int shiftCount);

	virtual Vector3 FindFurthestPoint(Vector3 direction);
};


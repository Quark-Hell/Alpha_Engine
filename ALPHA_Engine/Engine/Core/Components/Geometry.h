#pragma once
#include <memory>
#include <vector>
#include "Core/Components/Component.h"

 
namespace Core {

	class Geometry : public Component
	{
	protected:
		bool _isIndexed = false;

		std::shared_ptr<std::vector<float>> _vertex = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();

		virtual bool Create(const std::string& linkToFBX);
		virtual bool Create(const std::string& linkToFBX,
			const bool initIndices = true,
			const bool initVertex = true,
			const bool initNormals = true,
			const bool initTexCoord = false,
			const bool initMaterial = false);

	public:
		Geometry();
		~Geometry() override;
	};

}

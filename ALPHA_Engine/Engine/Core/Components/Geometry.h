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

		virtual bool Create(const std::string& linkToFBX,
			bool initIndices,
			bool initVertex,
			bool initNormals,
			bool initTexCoord);

	public:
		Geometry();
		~Geometry() override;
	};

}

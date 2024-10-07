#pragma once

#include "BaseConfig.h"
#include "Core/Components/Component.h"
 
namespace Core {

	class Geometry : public Component
	{
		friend class RenderCore;

	protected:
		bool _isIndexed = false;

		std::shared_ptr<std::vector<float>> _vertex = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();

	public:
		Geometry();
		virtual ~Geometry();
	};

}

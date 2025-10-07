#pragma once
#include <memory>
#include <vector>
#include "Core/Components/Component.h"
#include "Core/Math/glmMath.h"

namespace Core {

	class Geometry : public Component
	{
	protected:
		bool _isIndexed = false;

		std::shared_ptr<std::vector<float>> _vertices = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<float>> _normals = std::make_shared<std::vector<float>>();
		std::shared_ptr<std::vector<unsigned int>> _indices = std::make_shared<std::vector<unsigned int>>();

		virtual bool Create();

		virtual bool Create(const std::string& linkToFBX,
			bool initIndices,
			bool initVertex,
			bool initNormals,
			bool initTexCoord);

	public:
		Geometry();
		~Geometry() override;

		[[nodiscard]] std::shared_ptr<std::vector<float>> GetVertices() const noexcept;
		/**
		 * @brief Finds the furthest vertex of the geometry in a given direction.
		 *
		 * This function iterates over all vertices of the geometry and computes the
		 * dot product with the specified direction vector to determine which vertex
		 * is furthest along that direction.
		 *
		 * @param direction The direction vector along which to find the furthest point.
		 * @return A glm::vec3 representing the position of the furthest vertex along the given direction.
		 *
		 * @note The geometry's vertices are assumed to be stored as consecutive
		 *       x, y, z floats in the _vertices array.
		 */
		[[nodiscard]] glm::vec3 FindFurthestPoint(glm::vec3 direction) const;


		void MakeUnique();
	};

}

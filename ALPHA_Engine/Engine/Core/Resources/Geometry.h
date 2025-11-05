#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Resource.h"

#include "Core/Math/glmMath.h"

namespace Core {
	class Factory;

	class Geometry : public Core::Resource {
		friend class Factory;

	public:
		std::unique_ptr<std::vector<float>> Vertices = std::make_unique<std::vector<float>>();
		std::unique_ptr<std::vector<float>> Normals = std::make_unique<std::vector<float>>();
		std::unique_ptr<std::vector<unsigned int>> Indices = std::make_unique<std::vector<unsigned int>>();

		std::unique_ptr<std::vector<float>> VertexColors = std::make_unique<std::vector<float>>();
		std::unique_ptr<std::vector<float>> TexCoords = std::make_unique<std::vector<float>>();

		bool IsIndexed = false;

	public:
		Geometry() = default;
		~Geometry() = default;

		void LoadMesh(const std::string& linkToFBX,
			bool initVertex,
			bool initIndices,
			bool initNormals,
			bool initVertexColors,
			bool initTexCoord);

		[[nodiscard]] const std::vector<float>& GetVertices() const noexcept;
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
		 *       x, y, z floats in the Vertices array.
		 */
		[[nodiscard]] glm::vec3 FindFurthestPoint(glm::vec3 direction) const;


		void MakeUnique();
	};

}

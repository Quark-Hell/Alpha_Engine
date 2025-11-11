#pragma once
#include <memory>
#include <vector>
#include <string>
#include <optional>

#include "Resource.h"

#include "Core/Math/glmMath.h"

namespace Core {
	/*
	 * @brief Geometry load settings bit flags.
	 *
	 * This enum supports bitwise combinations of values.
	*/
	enum class GeometryLoadSettings : uint8_t {
		None = 0,
		InitVertex = 1 << 0,
		InitIndices = 1 << 1,
		InitNormals = 1 << 2,
		InitVertexColors = 1 << 3,
		InitTexCoord = 1 << 4,

		All = InitVertex | InitIndices | InitNormals | InitVertexColors | InitTexCoord
	};

	constexpr inline GeometryLoadSettings operator|(GeometryLoadSettings a, GeometryLoadSettings b) noexcept {
		return static_cast<GeometryLoadSettings>(
			static_cast<uint8_t>(a) | static_cast<uint8_t>(b)
			);
	}

	constexpr inline GeometryLoadSettings operator&(GeometryLoadSettings a, GeometryLoadSettings b) noexcept {
		return static_cast<GeometryLoadSettings>(
			static_cast<uint8_t>(a) & static_cast<uint8_t>(b)
			);
	}

	constexpr inline GeometryLoadSettings operator^(GeometryLoadSettings a, GeometryLoadSettings b) noexcept {
		return static_cast<GeometryLoadSettings>(
			static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b)
			);
	}

	constexpr inline GeometryLoadSettings operator~(GeometryLoadSettings a) noexcept {
		return static_cast<GeometryLoadSettings>(
			~static_cast<uint8_t>(a)
			);
	}

	constexpr inline GeometryLoadSettings& operator|=(GeometryLoadSettings& a, GeometryLoadSettings b) noexcept {
		a = a | b;
		return a;
	}

	constexpr inline GeometryLoadSettings& operator&=(GeometryLoadSettings& a, GeometryLoadSettings b) noexcept {
		a = a & b;
		return a;
	}

	/*
	 * @brief Check if a flag is set.
	 * @param value Bitmask to test.
	 * @param flag Specific flag to check.
	 * @return True if flag is present in value.
	*/
	constexpr inline bool HasFlag(GeometryLoadSettings value, GeometryLoadSettings flag) noexcept {
		return (static_cast<uint8_t>(value) & static_cast<uint8_t>(flag)) != 0;
	}
}

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

		GeometryLoadSettings _loadSettings;

	public:
		Geometry() = default;
		~Geometry() = default;

		void LoadMesh(const std::string& linkToFBX, GeometryLoadSettings loadSettings);

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

		/*
		* @brief Separating one mesh by loose parts.
		* 
		* Behavior looks like similar function in blender.
		* 
		* Function in development, so it not optimized and may work wrong.
		* 
		* @param geometry Geometry that should be separated
		* @return Vector of pointers to new Geometry. Or emtry value if function could not separate mesh
		* 
		* @note this function doesn't delete param	
		*/
		static std::optional<std::vector<Geometry*>> SeparateByLooseParts(const Geometry& geometry);

		static std::pair<std::vector<unsigned int>,unsigned int> GetUniqueIndices(const Geometry& geometry);

		void MakeUnique();
	};

}

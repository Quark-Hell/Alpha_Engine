#pragma once

#include <string>

namespace Core {
	class World;
	class Factory;

	class Resource {
		friend class World;
		friend class Factory;

	public:
		/// @brief Resource name
		std::string Name = "Resource";

	protected:
		Resource() = default;

	public:
		/// @brief Copy constructor (deleted)
		Resource(const Resource&) = delete;

		/// @brief Move constructor (deleted)
		Resource(Resource&&) = delete;

		/// @brief Copy assignment (deleted)
		Resource& operator=(const Resource&) = delete;

		/// @brief Move assignment (deleted)
		Resource& operator=(Resource&&) = delete;

	public:
		virtual ~Resource() = default;
	};
}
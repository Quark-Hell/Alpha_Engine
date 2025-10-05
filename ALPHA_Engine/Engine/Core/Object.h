#pragma once
#include <vector>
#include "Tag.h"

#include "Components/Transform.h"
#include "Core/Logger/Logger.h"

namespace Core {
	class Component;

	class Object
	{
		friend class Factory;

	private:
		std::string _name = "Undefined";
		std::vector<Component*> _components;
		Tag _tag;

	public:
		Transform transform;

	private:
		///Do not use this if you want to create new object. Use static method CreateObject for this!!!
		Object();

	public:
		~Object();

		void Delete();

		/**
		 * @brief Sets the name of the object.
		 * @param newName New name to assign to the object.
		 */
		void SetName(const std::string &newName);
		/**
		 * @brief Retrieves the current name of the object.
		 * @return The name of the object as a std::string.
		 */
		std::string GetName();

		/**
		 * @brief Adds a component to the object.
		 * @param component Reference to the component to add.
		 * @return True if the component was added successfully, false otherwise.
		 */
		bool AddComponent(Component& component);

		/**
		 * @brief Returns the number of components attached to the object.
		 * @return The count of components.
		 */
		[[nodiscard]] size_t GetCountOfComponents() const;

		/**
		 * @brief Deletes a component by its index.
		 * @param index Index of the component to delete.
		 * @return True if deletion was successful, false if the index was invalid.
		 */
		bool DeleteComponentByIndex(int index);


		/**
		 * @brief Computes and returns the object's transformation matrix.
		 * @return 4x4 transformation matrix combining position, rotation, and scale.
		 */
		glm::mat4x4 GetTransformMatrix();

		/**
		 * @brief Returns a constant reference to the first component of the specified type.
		 *
		 * Searches the internal component list and returns the first component that
		 * matches the requested type @p T. The search uses @c dynamic_cast to safely
		 * identify the component type.
		 *
		 * @tparam T The type of the component to retrieve.
		 * @return Constant reference to the first component of type @p T.
		 *
		 * @note Intended to be used internally by the #Object class for component access.
		 */
		template <typename T>
		const T& GetComponentByType() const {
			for (const auto* component : _components)
			{
				if (auto casted = dynamic_cast<const T*>(component))
				{
					return *casted;
				}
			}

			Logger::Logger::LogWarning(
				"Component of requested type not found " + std::string(__FILE__ ":") + std::to_string(__LINE__)
			);
		}

		/**
		 * @brief Returns all components that match the specified type.
		 *
		 * Searches the internal component list and returns all components that
		 * match the requested type @p T. The search uses @c dynamic_cast to safely
		 * identify the component type.
		 *
		 * @tparam T The type of components to retrieve.
		 * @return A vector of constant references to all components of type @p T.
		 *
		 * @note Intended to be used internally by the #Object class for component access.
		 */
		template <typename T>
		std::vector<std::reference_wrapper<const Core::Component>> GetComponentsByType() const
		{
			std::vector<std::reference_wrapper<const Core::Component>> result;

			for (const auto* component : _components)
			{
				if (dynamic_cast<const T*>(component))
				{
					result.push_back(*component);
				}
			}

			if (result.empty())
			{
				Logger::Logger::LogWarning(
					"No components of requested type found " + std::string(__FILE__ ":") + std::to_string(__LINE__)
				);
			}

			return result;
		}

		/**
		 * @brief Returns a constant reference to a component by its index.
		 *
		 * Retrieves the component stored at the specified index within the internal
		 * component list. If the provided index is out of range, an error is logged
		 * and an exception is thrown.
		 *
		 * @param index The zero-based index of the component to retrieve.
		 * @return Constant reference to the requested @c Component.
		 *
		 * @note Intended to be used internally by the #Object class for component access.
		 */
		 const Core::Component& GetComponentByIndex(size_t index) const;
	};

}

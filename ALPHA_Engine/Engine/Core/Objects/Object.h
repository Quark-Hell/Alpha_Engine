#pragma once

#include <vector>
#include "Core/Tag.h"

#include "Core/Components/Component.h"
#include "Core/Components/Transform.h"
#include "Core/Logger/Logger.h"

namespace Core {
	class Object
	{
	private:
		std::string _name = "Undefined";
		std::vector<Component*> _components;
		Tag _tag;

	public:
		Transform transform;

	protected:
		Object();

	public:
		virtual ~Object();

		/**
		 * @brief Sets the name of the object.
		 * @param newName New name to assign to the object.
		 */
		void SetName(const std::string& newName);
		/**
		 * @brief Retrieves the current name of the object.
		 * @return The name of the object as a std::string.
		 */
		std::string GetName();

		/**
		 * @brief Attaches (adds) a component to the object.
		 *
		 * This function registers the specified component within the object's internal
		 * component list.
		 *
		 * @param component Reference to the component to attach.
		 * @return True if the component was successfully added, false otherwise.
		 */
		bool AddComponent(Component& component);

		/**
		 * @brief Returns the number of components attached to the object.
		 * @return The count of components.
		 */
		[[nodiscard]] size_t GetCountOfComponents() const;

		/**
		 * @brief Detach a component by its index.
		 * @param index Index of the component to delete.
		 * @return True if deletion was successful, false if the index was invalid.
		 */
		bool DetachComponent(int index);

		bool DetachComponent(Component& ref);

		std::vector<Component*> GetComponents();

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
		T* GetComponentByType() const {
			for (auto* component : _components)
			{
				if (auto* casted = dynamic_cast<T*>(component))
				{
					return casted;
				}
			}

			Logger::Logger::LogWarning(
				"Component of requested type not found " + std::string(__FILE__ ":") + std::to_string(__LINE__)
			);

			return nullptr;
		}

		/**
		 * @brief Returns all components that match the specified type.
		 *
		 * Searches the internal component list and returns all components that
		 * match the requested type @p T. The search uses @c dynamic_cast to safely
		 * identify the component type.
		 *
		 * @tparam T The type of components to retrieve.
		 * @return A vector of references to all components of type @p T.
		 *
		 * @note Intended to be used internally by the #Object class for component access.
		 */
		template <typename T>
		requires std::is_base_of_v<Component, T>
		std::vector<std::reference_wrapper<T>> GetComponentsByType() const
		{
			std::vector<std::reference_wrapper<T>> result;

			for (auto* component : _components)
			{
				if (auto* comp = dynamic_cast<T*>(component))
				{
					result.push_back(*comp);
				}
			}

			if (result.empty())
			{
				Logger::Logger::LogWarning(
					"No components of requested type found " + __LOGERROR__);
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
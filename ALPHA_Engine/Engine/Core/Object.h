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

		void SetName(const std::string &newName);
		std::string GetName();

		bool AddComponent(Component& component);

		[[nodiscard]] size_t GetCountOfComponents() const;

		bool DeleteModuleByIndex(int index);

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

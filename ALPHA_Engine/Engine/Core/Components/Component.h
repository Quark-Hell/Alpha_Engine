#pragma once
#include <string>
#include <vector>

namespace Core {
	class Object;
	class GameObject;
	class FakeObject;

	class Component
	{
		friend class Object;
		friend class GameObject;
		friend class FakeObject;

	public:
		std::string Name = "Undefined";

	protected:
		Object* _parentObject = nullptr;

	protected:
		Component() = default;

		/**
		 * @brief Performs internal adjustments when the parent object changes.
		 *
		 * This method is used for additional internal configuration of the component
		 * when its parent object is modified. It should only be called by the
		 * #Object class. Calling this function from any other context results in
		 * undefined behavior.
		 * 
		 * @param newParent Reference to the object to which the component is being added.
		 */
		void virtual UpdateParentObject(Core::Object& newParent);

		/**
		 * @brief Checks whether the component can be added to the specified object.
		 *
		 * This function determines if the current component can be attached to the given object.
		 * It is primarily used to restrict adding components that must exist in a single instance
		 * per object (for example, Rigidbody).
		 *
		 * Derived component classes can override this method to implement custom validation logic.
		 *
		 * @param newParent Reference to the object to which the component is being added.
		 * @return `true` if the component can be added to the specified object; otherwise, `false`.
		 */
		bool virtual CheckAddPossibility(Core::Object& newParent);

	public:
		virtual ~Component() = default;
		Component(const Component&) = delete;

		//virtual void Delete() = 0;

		Object* GetParentObject() const noexcept;

		void RemoveParent() noexcept;
	};

}
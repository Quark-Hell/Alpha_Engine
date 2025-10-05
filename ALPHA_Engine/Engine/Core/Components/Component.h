#pragma once
#include <string>

namespace Core {
	class Object;

	class Component
	{
		friend class Object;

	public:
		std::string Name = "Undefined";

	protected:
		Object* ParentObject = nullptr;

	protected:
		Component() = default;

		/**
		 * @brief Performs internal adjustments when the parent object changes.
		 *
		 * This method is used for additional internal configuration of the component
		 * when its parent object is modified. It should only be called by the
		 * #Object class. Calling this function from any other context results in
		 * undefined behavior.
		 */
		void virtual UpdateParentObject();

	public:
		virtual ~Component();
		Component(const Component&) = delete;

		//virtual void Delete() = 0;

		Object* GetParentObject();
	};

}
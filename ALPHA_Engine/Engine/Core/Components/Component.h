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

	public:
		virtual ~Component();
		Component(const Component&) = delete;

		//virtual void Delete() = 0;

		Object* GetParentObject();
	};

}
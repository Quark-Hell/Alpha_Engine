#pragma once
#include "BaseConfig.h"

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
		Component();

	public:
		virtual ~Component();

		//virtual void Delete() = 0;

		Object* GetParentObject();
	};

}
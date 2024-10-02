#pragma once
#include "BaseConfig.h"

namespace Core {
	class Object;

	class Component
	{
	public:
		std::string Name = "Undefined";

	protected:
		Object* ParentObject = nullptr;

	protected:
		Component();

	public:
		virtual ~Component();

		virtual void Delete();

		Object& GetParentObject();
		virtual void SetParentObject(const Core::Object& parent);
	};

}
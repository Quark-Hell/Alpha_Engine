#pragma once
#include "BaseConfig.h"


enum ModulesList : unsigned short;

namespace Core {
	class Object;

	class Module
	{
	public:
		std::string Name = "Undefined";

	protected:
		Object* ParentObject = nullptr;

	public:
		Module();
		virtual ~Module();

		virtual void Delete();

		virtual ModulesList GetType() = 0;

		virtual Object* GetParentObject();
		virtual void SetParentObject(const Core::Object& parent);
	};

}
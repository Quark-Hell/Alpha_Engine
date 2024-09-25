#pragma once
#include "BaseConfig.h"

class Object;
enum ModulesList : unsigned short;

namespace Core {

	class Module
	{
	public:
		std::string Name = "Undefined";

	protected:
		Object* ParentObject = nullptr;

	public:
		Module();
		~Module();

		virtual void Delete();

		virtual ModulesList GetType() = 0;

		virtual Object* GetParentObject();
		virtual void SetParentObject(const Object& parent);
	};

}
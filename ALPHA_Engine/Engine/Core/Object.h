#pragma once
#include "BaseConfig.h"

#include "Tag.h"
//#include "Components/Transform.h"

namespace Core {
	class Component;

	class Object
	{
	private:
		std::string _name = "Undefined";
		//Transform _transform;
		std::vector<std::shared_ptr<Core::Component>> _modules;
		Tag _tag;

	private:
		//Do not use this if you want to create new object. Use static method CreateObject for this!!!
		Object();

	public:
		static std::shared_ptr<Core::Object> CreateObject(const std::string& name);
		~Object();

		void Delete();

		void SetName(std::string newName);
		std::string GetName();

		int GetCountOfModules();

		bool DeleteModuleByIndex(int index);

		//std::shared_ptr<Core::Component> GetModuleByType(ModulesList type);
		//std::vector<std::shared_ptr<Core::Component>> GetModuleByTypes(std::vector<ModulesList> typesArray);
		//std::shared_ptr<Core::Component> GetModuleByIndex(size_t index);
	};

}

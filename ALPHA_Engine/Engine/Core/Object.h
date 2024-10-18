#pragma once
#include "BaseConfig.h"

#include "Tag.h"
#include "Components/Transform.h"

namespace Core {
	class Component;

	class Object
	{
		friend class Factory;

	private:
		std::string _name = "Undefined";
		Transform _transform;
		std::vector<std::shared_ptr<Core::Component>> _components;
		Tag _tag;

	private:
		///Do not use this if you want to create new object. Use static method CreateObject for this!!!
		Object();

	public:
		static Core::Object& CreateObject(const std::string& name = "Undefined");

		~Object();

		void Delete();

		void SetName(const std::string &newName);
		std::string GetName();

		[[nodiscard]] size_t GetCountOfComponents() const;

		bool DeleteModuleByIndex(int index);

		//std::shared_ptr<Core::Component> GetModuleByType(ModulesList type);
		//std::vector<std::shared_ptr<Core::Component>> GetModuleByTypes(std::vector<ModulesList> typesArray);
		//std::shared_ptr<Core::Component> GetModuleByIndex(size_t index);
	};

}

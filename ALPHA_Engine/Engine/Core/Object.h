#pragma once
#include <vector>
#include "Tag.h"
#include "Components/Transform.h"

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

		bool AddComponent(Component* component);

		[[nodiscard]] size_t GetCountOfComponents() const;

		bool DeleteModuleByIndex(int index);

		glm::mat4x4 GetTransformMatrix();

		//std::shared_ptr<Core::Component> GetModuleByType(ModulesList type);
		//std::vector<std::shared_ptr<Core::Component>> GetModuleByTypes(std::vector<ModulesList> typesArray);
		//std::shared_ptr<Core::Component> GetModuleByIndex(size_t index);
	};

}

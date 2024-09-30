#pragma once
class Module;

#include "BaseConfig.h"

#include "Tag.h"
#include "Modules/Transform.h"

enum ModulesList : unsigned short;

namespace Core {
	class Module;

	class Object
	{
	private:
		std::string _name = "Undefined";
		Transform _transform;
		std::vector<std::shared_ptr<Core::Module>> _modules = std::vector<std::shared_ptr<Core::Module>>();
		Tag _tag;

	public:
		Object();
		~Object();

		void Delete();

		void SetName(std::string newName);
		std::string GetName();

		bool AddModule(std::shared_ptr<Core::Module> someModule);
		bool AddModule(ModulesList moduleType, Core::Module** outputModule);
		bool AddModule(ModulesList moduleType);

		int GetCountOfModules();

		bool DeleteModuleByType(ModulesList type);
		bool DeleteModuleByIndex(int index);

		std::shared_ptr<Core::Module> GetModuleByType(ModulesList type);
		std::vector<std::shared_ptr<Core::Module>> GetModuleByTypes(std::vector<ModulesList> typesArray);
		std::shared_ptr<Core::Module> GetModuleByIndex(size_t index);
	};

}
#pragma once
class Module;

#include "BaseConfig.h"
#include "ModuleList.h"

#include "Core/Tag.h"
#include "Core/Modules/Transform.h"

class Object
{
private:
	Transform _transform;
	std::vector<std::shared_ptr<Module>> _modules = std::vector<std::shared_ptr<Module>>();
	Tag _tag;

public:
	Object();
	~Object();

	void Delete();

	bool AddModule(std::shared_ptr<Module> someModule);
	bool AddModule(ModulesList moduleType, Module** outputModule);
	bool AddModule(ModulesList moduleType);

	int GetCountOfModules();

	bool DeleteModuleByType(ModulesList type);
	bool DeleteModuleByIndex(int index);

	std::shared_ptr<Module> GetModuleByType(ModulesList type);
	std::vector<std::shared_ptr<Module>> GetModuleByTypes(std::vector<ModulesList> typesArray);
	std::shared_ptr<Module> GetModuleByIndex(size_t index);
};
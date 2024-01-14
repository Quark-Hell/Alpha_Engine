#include "Module.h"
#include "SubModules/SubModule.h"
#include "Object.h"

Module::Module() {

}
Module::~Module() {

}

ModulesList Module::GetType() {
	return ModulesList::ModuleType;
}

Object* Module::GetParentObject() {
	return ParentObject;
}
void Module::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

bool Module::AddSubModule(std::shared_ptr<SubModule> subModule) {
	return false;
}

bool Module::AddSubModule(SubModulesList type) {
	return false;
}

std::shared_ptr<SubModule> Module::GetSubModuleByType(SubModulesList type) {
	for (int i = 0; i < Module::_subModules.size(); i++) {
		if (Module::_subModules[i]->GetType() == type) {
			return Module::_subModules[i];
		}
	}

	return false;
}
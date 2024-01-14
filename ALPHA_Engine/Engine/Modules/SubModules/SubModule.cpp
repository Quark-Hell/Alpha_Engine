#include "SubModule.h"

SubModule::SubModule() {

}
SubModule::~SubModule() {

}

SubModulesList SubModule::GetType() {
	return SubModulesList::SubModuleType;
}

Module* SubModule::GetParentModule() {
	return ParentModule;
}
void SubModule::SetParentModule(const Module& parent) {
	ParentModule = const_cast<Module*>(&parent);
}
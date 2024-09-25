#include "Module.h"
#include "ModuleList.h"

Core::Module::Module() {

}
Core::Module::~Module() {

}

void Core::Module::Delete(){

}

ModulesList Core::Module::GetType() {
	return ModulesList::ModuleType;
}

Object* Core::Module::GetParentObject() {
	return ParentObject;
}
void Core::Module::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}
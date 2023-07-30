#include "Module.h"
#include "Object.h"

ModulesList Module::GetType() {
	return ModulesList::ModuleType;
}

Object* Module::GetParentObject() {
	return ParentObject;
}
void Module::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

Module::Module() {

}
Module::~Module() {

}
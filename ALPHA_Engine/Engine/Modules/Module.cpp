#include "Module.h"
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

void Module::ModuleAdded()
{
}

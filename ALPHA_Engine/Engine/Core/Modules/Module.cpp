#include "Module.h"
#include "ModuleList.h"

Module::Module() {

}
Module::~Module() {

}

void Module::Delete(){

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
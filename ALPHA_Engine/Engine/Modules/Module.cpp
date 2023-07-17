#include "Module.h"

#include "Object.h"

Object* Module::GetParentObject() {
	return ParentObject;
}

void Module::Test() {

}

ModulesList Module::GetType() {
	return ModulesList::ModuleType;
}

void Module::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

Module::Module() {

}
Module::~Module() {

}
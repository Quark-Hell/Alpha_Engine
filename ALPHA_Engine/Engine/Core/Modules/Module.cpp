#include "Module.h"
#include "ModuleList.h"

#include "Core/Object.h"

Core::Module::Module() {

}
Core::Module::~Module() {

}

void Core::Module::Delete(){

}

ModulesList Core::Module::GetType() {
	return ModulesList::ModuleType;
}

Core::Object* Core::Module::GetParentObject() {
	return ParentObject;
}
void Core::Module::SetParentObject(const Core::Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}
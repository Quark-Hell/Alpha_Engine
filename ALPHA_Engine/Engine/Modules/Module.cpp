#include "Module.h"

#include "Object.h"

inline Object* Module::GetParentObject() {
	return ParentObject;
}

inline void Module::Test() {

}

inline ModulesList Module::GetType() {
	return ModulesList::ModuleType;
}

inline Module::Module() {

}
inline Module::~Module() {

}
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

inline void Module::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

inline Module::Module() {

}
inline Module::~Module() {

}
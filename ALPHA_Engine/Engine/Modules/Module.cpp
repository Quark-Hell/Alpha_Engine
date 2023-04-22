#include "Module.h"

#include "Object.h"

inline void Module::Rename(std::string name) {
	_name = name;
}
inline std::string Module::GetName() {
	return Module::_name;
}

inline Object* Module::GetParentObject() {
	return ParentObject;
}

inline void Module::Test() {

}
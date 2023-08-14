#include "Mesh.h"

#pragma region Mesh Define
Mesh::Mesh() {

}
inline Mesh::~Mesh() {

}

inline ModulesList Mesh::GetType() {
	return ModulesList::MeshType;
}

void Mesh::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

#pragma endregion
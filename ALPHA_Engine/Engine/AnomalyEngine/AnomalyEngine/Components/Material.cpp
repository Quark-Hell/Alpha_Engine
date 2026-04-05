#include "Material.h"

namespace AnomalyEngine {

    Material::Material(Mesh* parent) : _parentMesh(parent) {

    }

    Mesh* Material::GetParentMesh() const {
        return _parentMesh;
    }

}


#include "Material.h"

namespace AnomalyEngine::Render{

    Material::Material(const Components::Mesh* parent) : _parentMesh(parent) {

    }

    const Components::Mesh* Material::GetParentMesh() const {
        return _parentMesh;
    }

}


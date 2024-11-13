#include "Material.h"

namespace Render::AnomalyEngine {

    Material::Material(Components::Mesh* parent) : _parentMesh(parent) {

    }

    Components::Mesh* Material::GetParentMesh() const {
        return _parentMesh;
    }

}


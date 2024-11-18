#include "Material.h"

namespace Render::WindowsManager::AnomalyEngine {

    Material::Material(Mesh* parent) : _parentMesh(parent) {

    }

    Mesh* Material::GetParentMesh() const {
        return _parentMesh;
    }

}


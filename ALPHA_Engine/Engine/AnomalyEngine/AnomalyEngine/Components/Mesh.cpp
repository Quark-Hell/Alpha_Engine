#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "AnomalyEngine/Resources/Binder.h"

#include "Core/Logger/Logger.h"

namespace AnomalyEngine {
    Mesh::~Mesh() {
        //TODO: Delete mesh info from VRAM
    }

    bool Mesh::LoadMesh(Core::Geometry& geometry, std::shared_ptr<AnomalyEngine::Binder> binder) {
        _geometry = &geometry;

        if (binder != nullptr) {
            _binder = binder;
        }
        else
        {
            _binder = std::make_shared<AnomalyEngine::Binder>();
            _binder->BindMesh(*this);
        }

        return true;
    }

    unsigned int Mesh::GetVertexVbo() const noexcept {
        if (_binder == nullptr) {
            return 0;
        }

        return _binder->_vertexVbo;
    }
    unsigned int Mesh::GetColorsVbo() const noexcept {
        if (_binder == nullptr) {
            return 0;
        }

        return _binder->_colorsVbo;
    }
    unsigned int Mesh::GetNormalsVbo() const noexcept {
        if (_binder == nullptr) {
            return 0;
        }

        return _binder->_normalsVbo;
    }
    unsigned int Mesh::GetTexCoordsVbo() const noexcept {
        if (_binder == nullptr) {
            return 0;
        }

        return _binder->_texCoordsVbo;
    }

    const Core::Geometry* Mesh::GetGeometry() const noexcept {
        return _geometry;
    }
}

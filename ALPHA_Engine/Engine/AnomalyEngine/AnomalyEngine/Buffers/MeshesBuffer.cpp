#include "MeshesBuffer.h"

namespace AnomalyEngine {
    MeshesBuffer::MeshesBuffer(size_t initialBufferSize) : TSystemData("MeshBuffer", initialBufferSize) {}

    Mesh& MeshesBuffer::CreateMesh() {
        _data.emplace_back(std::unique_ptr<Mesh>(new Mesh()));

        return *_data.back().get();
    }

    Mesh& MeshesBuffer::CreateMesh(Core::Geometry& geometry, std::shared_ptr<AnomalyEngine::Binder> binder) {
        _data.emplace_back(std::unique_ptr<Mesh>(new Mesh()));
        _data.back().get()->LoadMesh(geometry, binder);

        return *_data.back().get();
    }
}

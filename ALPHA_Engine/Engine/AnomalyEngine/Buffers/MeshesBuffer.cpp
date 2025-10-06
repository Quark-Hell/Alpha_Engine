#include "MeshesBuffer.h"

namespace AnomalyEngine {
    MeshesBuffer::MeshesBuffer(size_t initialBufferSize) : TSystemData("MeshBuffer", initialBufferSize) {}

    Mesh& MeshesBuffer::CreateMesh() {
        _data.emplace_back(std::unique_ptr<Mesh>(new Mesh()));
        _data.back().get()->Create();

        return *_data.back().get();
    }

    Mesh& MeshesBuffer::CreateMesh(
            const std::string& linkToFBX,
            const bool initIndices,
            const bool initVertex,
            const bool initNormals,
            const bool initTexCoord) {

        _data.emplace_back(std::unique_ptr<Mesh>(new Mesh()));
        _data.back().get()->Create(linkToFBX, initIndices, initVertex, initNormals, initTexCoord);

        return *_data.back().get();
    }
}

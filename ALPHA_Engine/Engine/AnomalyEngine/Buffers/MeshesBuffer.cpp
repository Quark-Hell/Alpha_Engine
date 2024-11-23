#include "MeshesBuffer.h"

namespace AnomalyEngine {
    MeshesBuffer::MeshesBuffer() : TSystemData("MeshBuffer") {
        _data.reserve(64);
    }

    Mesh* MeshesBuffer::CreateMesh(
            const std::string& linkToFBX,
            const bool initIndices,
            const bool initVertex,
            const bool initNormals,
            const bool initTexCoord) {

        _data.emplace_back(std::unique_ptr<Mesh>(new Mesh()));
        _data.back().get()->Create(linkToFBX, initIndices, initVertex, initNormals, initTexCoord);

        return _data.back().get();
    }
}

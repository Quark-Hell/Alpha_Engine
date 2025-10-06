#pragma once

#include "AnomalyEngine/Components/Mesh.h"
#include "Core/ECS/TSystemData.h"

namespace AnomalyEngine {
    class MeshesBuffer final : public Core::TSystemData<Mesh> {
        friend class RenderEngine;

        public:
        MeshesBuffer(size_t initialBufferSize = 0);
        ~MeshesBuffer() override = default;

        Mesh& CreateMesh();

        Mesh& CreateMesh(
                    const std::string& linkToFBX,
                    bool initIndices = true,
                    bool initVertex = true,
                    bool initNormals = true,
                    bool initTexCoord = true);
    };
}


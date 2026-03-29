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

        Mesh& CreateMesh(Core::Geometry& geometry, std::shared_ptr<AnomalyEngine::Binder> binder = nullptr);
    };
}


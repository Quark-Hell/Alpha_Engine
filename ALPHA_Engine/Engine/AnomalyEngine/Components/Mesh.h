#pragma once

#include "Material.h"

#include "AnomalyEngine/Resources/Binder.h"

#include "Core/Components/Component.h"
#include "Core/Resources/Geometry.h"

namespace AnomalyEngine {
    class Mesh : public Core::Component {
        friend class MeshesBuffer;
        friend class Binder;
        friend class RenderEngine;

    protected:
        Core::Geometry* _geometry;
        std::shared_ptr<AnomalyEngine::Binder> _binder;

    public:
        Material _material{this};

    protected:
        Mesh() = default;

    public:
        bool LoadMesh(Core::Geometry& geometry, std::shared_ptr<AnomalyEngine::Binder> binder = nullptr);

        virtual ~Mesh();

        [[nodiscard]] const Core::Geometry* GetGeometry() const noexcept;

        [[nodiscard]] unsigned int GetVertexVbo() const noexcept;
        [[nodiscard]] unsigned int GetColorsVbo() const noexcept;
        [[nodiscard]] unsigned int GetNormalsVbo() const noexcept;
        [[nodiscard]] unsigned int GetTexCoordsVbo() const noexcept;
    };
}


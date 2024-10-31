#pragma once

#include "Core/Components/Geometry.h"
#include "Material.h"

namespace Core {
    class Factory;
}

namespace Render::AnomalyEngine {
    class RenderEngine;
    class Binder;
}

namespace Render::AnomalyEngine::Components {
    class Mesh : public Core::Geometry {
        friend class Core::Factory;
        friend class Render::AnomalyEngine::RenderEngine;
        friend class Render::AnomalyEngine::Binder;

    private:
        Mesh();

    protected:
        std::unique_ptr<std::vector<float>> _vertexColors = std::make_unique<std::vector<float>>();
        std::unique_ptr<std::vector<float>> _texCoords = std::make_unique<std::vector<float>>();

        unsigned int _vertexVbo = 0;
        unsigned int _colorsVbo = 0;
        unsigned int _normalsVbo = 0;
        unsigned int _texCoordsVbo = 0;
        unsigned int _vao = 0;

    public:
        Material _material{this};

    public:
        ~Mesh() override;

        bool Create(const std::string& linkToFBX) override;
        bool Create(
            const std::string& linkToFBX,
            const bool initIndices,
            const bool initVertex,
            const bool initNormals,
            const bool initTexCoord,
            const bool initMaterial) override;

        bool LoadTextureCoord(std::string pathToCoords);
    };
}


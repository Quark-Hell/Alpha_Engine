#pragma once

#include "Core/Components/Geometry.h"
#include "Material.h"

namespace AnomalyEngine {
    class Mesh : public Core::Geometry {
        friend class MeshesBuffer;
        friend class Binder;
        friend class RenderEngine;

    protected:
        std::unique_ptr<std::vector<float>> _vertexColors = std::make_unique<std::vector<float>>();
        std::unique_ptr<std::vector<float>> _texCoords = std::make_unique<std::vector<float>>();

        unsigned int _vertexVbo = 0;
        unsigned int _colorsVbo = 0;
        unsigned int _normalsVbo = 0;
        unsigned int _texCoordsVbo = 0;

    public:
        Material _material{this};

    private:
        Mesh();
        bool Create(
            const std::string& linkToFBX,
            bool initIndices = true,
            bool initVertex = true,
            bool initNormals = true,
            bool initTexCoord = true) override;

    public:
        ~Mesh() override;

        [[nodiscard]] unsigned int GetVertexVbo() const;
        [[nodiscard]] unsigned int GetColorsVbo() const;
        [[nodiscard]] unsigned int GetNormalsVbo() const;
        [[nodiscard]] unsigned int GetTexCoordsVbo() const;

        bool LoadTextureCoord(std::string pathToCoords);
    };
}


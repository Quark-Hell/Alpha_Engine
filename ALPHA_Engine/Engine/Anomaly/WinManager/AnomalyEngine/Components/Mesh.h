#pragma once

#include "Core/Components/Geometry.h"

namespace Core {
    class Factory;
}

namespace AnomalyEngine::Render {
    class Mesh : public Core::Geometry {
        friend class Core::Factory;

    private:
        Mesh();

    protected:
        std::shared_ptr<std::vector<float>> _vertexColors = std::make_shared<std::vector<float>>();
        std::shared_ptr<std::vector<float>> _texCoords = std::make_shared<std::vector<float>>();

        unsigned int _vertexVbo = 0;
        unsigned int _colorsVbo = 0;
        unsigned int _normalsVbo = 0;
        unsigned int _texCoordsVbo = 0;
        unsigned int _vao = 0;

    public:
        //std::shared_ptr<Material> _material = std::make_shared<Material>();

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

        bool BindMesh();
    };
}


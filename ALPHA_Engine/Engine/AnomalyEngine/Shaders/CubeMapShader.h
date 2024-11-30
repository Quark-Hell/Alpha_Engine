#pragma once

#include "TShaderProgram.h"
#include "AnomalyEngine/Textures/OpenGLTexture.h"

#include <array>

namespace AnomalyEngine {
    class CubeMapShader final : public ShaderProgram {
    private:
        std::array<OpenGLTexture, 6> _cubemapTextures;
        uint32_t _textureId = 0;

    public:
        CubeMapShader(Material* parentMat);
        ~CubeMapShader() override = default;

        void LoadTextures(
            const std::string& leftSide,
            const std::string& rightSide,
            const std::string& topSide,
            const std::string& bottomSide,
            const std::string& frontSide,
            const std::string& backSide);

        bool TransferTexturesToGPU();

        void ApplyShadersSettings(Camera &camera) override;
    };
}



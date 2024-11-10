#pragma once

#include "ShaderProgram.h"
#include "Render/WinManager/AnomalyEngine/Textures/OpenGLTexture.h"

#include <array>

namespace Render::AnomalyEngine::Shaders {

    class CubeMapShader final : public ShaderProgram {
    private:
        std::array<Textures::OpenGLTexture, 6> _cubemapTextures;

        unsigned int _textureId = 0;

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

        void ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) override;
    };

}



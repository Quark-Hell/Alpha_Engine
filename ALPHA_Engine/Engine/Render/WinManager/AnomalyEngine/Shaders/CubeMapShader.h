#pragma once

#include "ShaderProgram.h"
#include "Render/WinManager/AnomalyEngine/Textures/OpenGLTexture.h"

namespace Render::AnomalyEngine::Shaders {

    class CubeMapShader final : public ShaderProgram {
    private:
        Textures::OpenGLTexture _rightSide;
        Textures::OpenGLTexture _leftSide;
        Textures::OpenGLTexture _topSide;
        Textures::OpenGLTexture _bottomSide;
        Textures::OpenGLTexture _frontSide;
        Textures::OpenGLTexture _backSide;

        unsigned int _textureId = 0;

    public:
        CubeMapShader(Material* parentMat);
        ~CubeMapShader() override = default;

        bool LoadTexture();

        void ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) override;
    };

}



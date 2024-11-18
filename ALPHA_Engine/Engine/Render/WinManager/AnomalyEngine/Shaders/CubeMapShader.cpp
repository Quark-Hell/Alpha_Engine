#include "CubeMapShader.h"

#include <Core/Object.h>
#include <GLEW/glew.h>

#include <Render/WinManager/AnomalyEngine/Components/Camera.h>
#include "Render/WinManager/AnomalyEngine/Textures/BaseTexture.h"
#include "Render/WinManager/AnomalyEngine/Textures/TextureLoader.h"

#include "Logger/Logger.h"

#include "Core/Timer.h"

namespace Render::AnomalyEngine::Textures {
    enum EnumTypeOfTexture : unsigned short;
}

namespace Render::AnomalyEngine::Shaders {

    CubeMapShader::CubeMapShader(Material* parentMat): ShaderProgram(parentMat) {
        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/CubeMapShader/VertexShader.txt)", ShadersType::VertexShader);
        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/CubeMapShader/FragmentShader.txt)", ShadersType::FragmentShader);

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            Logger::Logger::LogError("Cube map shader was not be created: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        Logger::Logger::LogInfo("Cube map shader was be created");
    }

    void CubeMapShader::LoadTextures(
        const std::string& leftSide,
        const std::string& rightSide,
        const std::string& topSide,
        const std::string& bottomSide,
        const std::string& frontSide,
        const std::string& backSide) {

        {
            Core::ScopedTimer timer("Load time");

            const auto loader = Textures::TextureLoader::GetInstance();
            loader->AddTask(_cubemapTextures[0], leftSide);
            loader->AddTask(_cubemapTextures[1], rightSide);
            loader->AddTask(_cubemapTextures[2], topSide);
            loader->AddTask(_cubemapTextures[3], bottomSide);
            loader->AddTask(_cubemapTextures[4], frontSide);
            loader->AddTask(_cubemapTextures[5], backSide);
            loader->DoWork();
        }

        TransferTexturesToGPU();
    }

    bool CubeMapShader::TransferTexturesToGPU() {
        if (_textureId != 0) {
            glDeleteTextures(1, &_textureId);
            _textureId = 0;
            Logger::Logger::LogInfo("Old texture was deleted from VRAM");
        }

        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapShader::_textureId);

        for (size_t i = 0; i < _cubemapTextures.size(); i++) {
            if (!_cubemapTextures[i].TransferToGPU(false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + i)))
                return false;
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for (auto& _cubemapTexture : _cubemapTextures) {
            _cubemapTexture.DeleteTextureFromRAM();
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return true;
    }

    void CubeMapShader::ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) {
        if (camera->GetParentObject() == nullptr) {
            Logger::Logger::LogError("camera parent was null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }

        auto view = glm::mat4(glm::mat3(camera->GetParentObject()->GetTransformMatrix()));
        SetValue(UniformType::mat4x4,"view_matrix", &view);

        auto projMatrix = camera->GetProjectionMatrix();
        SetValue(UniformType::mat4x4, "projection_matrix", &projMatrix);

        glDepthFunc(GL_LEQUAL);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }
}

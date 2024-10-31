#include "CubeMapShader.h"

#include <Core/Object.h>
#include <Render/WinManager/AnomalyEngine/Components/Camera.h>

#include "Render/WinManager/AnomalyEngine/Textures/BaseTexture.h"

namespace Render::AnomalyEngine::Textures {
    enum EnumTypeOfTexture : unsigned short;
}

namespace Render::AnomalyEngine::Shaders {

    CubeMapShader::CubeMapShader(Material* parentMat): ShaderProgram(parentMat) {
        _rightSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Right_Tex.tga)");
        _leftSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Left_Tex.tga)");
        _topSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Top_Tex.tga)");
        _bottomSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Bottom_Tex.tga)");
        _frontSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Front_Tex.tga)");
        _backSide.CreateTexture(R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Back_Tex.tga)");

        LoadTexture();


        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/CubeMapShader/VertexShader.txt)", ShadersType::VertexShader);
        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/CubeMapShader/FragmentShader.txt)", ShadersType::FragmentShader);

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            std::cout << "Error: Cube map shader was not be created" << std::endl;
        }

        std::cout << "Info: Cube map shader was be created" << std::endl;
    }

    bool CubeMapShader::LoadTexture() {
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapShader::_textureId);

        if (!CubeMapShader::_leftSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 0)))
            return false;

        if (!CubeMapShader::_rightSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 1)))
            return false;

        if (!CubeMapShader::_topSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 2)))
            return false;

        if (!CubeMapShader::_bottomSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 3)))
            return false;

        if (!CubeMapShader::_frontSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 4)))
            return false;

        if (!CubeMapShader::_backSide.TransferToGPU(false, false, static_cast<Textures::EnumTypeOfTexture>(Textures::EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 5)))
            return false;

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        CubeMapShader::_rightSide.DeleteTexture();
        CubeMapShader::_leftSide.DeleteTexture();
        CubeMapShader::_topSide.DeleteTexture();
        CubeMapShader::_bottomSide.DeleteTexture();
        CubeMapShader::_frontSide.DeleteTexture();
        CubeMapShader::_backSide.DeleteTexture();

        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }

    void CubeMapShader::ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) {
        if (camera->GetParentObject() == nullptr) {
            std::cout << "Error: camera parent was null" << std::endl;
            return;
        }

       auto view = glm::mat4(glm::mat3(camera->GetParentObject()->GetTransformMatrix()));
       SetValue("view_matrix", view);

        auto projMatrix = camera->GetProjectionMatrix();
        SetValue("projection_matrix", projMatrix);

        glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
        glPolygonMode(GL_FRONT, GL_FILL);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }
}

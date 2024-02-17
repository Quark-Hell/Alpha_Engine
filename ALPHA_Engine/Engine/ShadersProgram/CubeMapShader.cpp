#include "CubeMapShader.h"
#include "Modules/Material.h"


CubeMapShader::CubeMapShader(Material* parentMat) : ShaderProgram(parentMat)
{
    CubeMapShader::LoadTexture(
        "\\Textures\\CubeMap\\Right_Tex.png",
        "\\Textures\\CubeMap\\Left_Tex.png",
        "\\Textures\\CubeMap\\Top_Tex.png",
        "\\Textures\\CubeMap\\Bottom_Tex.png",
        "\\Textures\\CubeMap\\Front_Tex.png",
        "\\Textures\\CubeMap\\Back_Tex.png");

    CubeMapShader::CreateShader("\\Shaders\\CubeMapShader\\VertexShader.txt", ShadersType::VertexShader);
    CubeMapShader::CreateShader("\\Shaders\\CubeMapShader\\FragmentShader.txt", ShadersType::FragmentShader);

    CubeMapShader::InitShader();
}

CubeMapShader::~CubeMapShader()
{
}

bool CubeMapShader::LoadTexture(std::string rightTexture, std::string leftTexture, std::string topTexture, std::string bottomTexture, std::string frontTexture, std::string backTexture)
{
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapShader::_textureId);

    CubeMapShader::_rightSide.CreateTexture(rightTexture.c_str());
    CubeMapShader::_leftSide.CreateTexture(leftTexture.c_str());
    CubeMapShader::_topSide.CreateTexture(topTexture.c_str());
    CubeMapShader::_bottomSide.CreateTexture(bottomTexture.c_str());
    CubeMapShader::_frontSide.CreateTexture(frontTexture.c_str());
    CubeMapShader::_backSide.CreateTexture(backTexture.c_str());

    CubeMapShader::_rightSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 1));
    CubeMapShader::_leftSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 0));
    CubeMapShader::_topSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 2));
    CubeMapShader::_bottomSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 3));
    CubeMapShader::_frontSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 4));
    CubeMapShader::_backSide.TransferToGPU(false, false, (EnumTypeOfTexture)(EnumTypeOfTexture::TEXTURE_CUBE_MAP_POSITIVE_X + 5));
    
    //CubeMapShader::_rightSide.CreateTexture(rightTexture.c_str());
    //if (!CubeMapShader::_rightSide.TransferToGPU(false, false))
    //    return false;
    //
    //CubeMapShader::_leftSide.CreateTexture(leftTexture.c_str());
    //if (!CubeMapShader::_leftSide.TransferToGPU(false, false))
    //    return false;
    //
    //CubeMapShader::_topSide.CreateTexture(topTexture.c_str());
    //if (!CubeMapShader::_topSide.TransferToGPU(false, false))
    //    return false;
    //
    //CubeMapShader::_bottomSide.CreateTexture(bottomTexture.c_str());
    //if (!CubeMapShader::_bottomSide.TransferToGPU(false, false))
    //    return false;
    //
    //CubeMapShader::_frontSide.CreateTexture(frontTexture.c_str());
    //if (!CubeMapShader::_frontSide.TransferToGPU(false, false))
    //    return false;
    //
    //CubeMapShader::_backSide.CreateTexture(backTexture.c_str());
    //if (!CubeMapShader::_backSide.TransferToGPU(false, false))
    //    return false;
    
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

void CubeMapShader::ApplyShadersSettings(std::shared_ptr<Camera> camera)
{
    CubeMapShader::SetValue(ShadersType::VertexShader, "projection_matrix", &camera->GetProjectionMatrix());
    //CubeMapShader::SetValue(ShadersType::VertexShader, "view_matrix", &camera->GetTransformMatrix());

    glm::mat4 view = glm::mat4(glm::mat3(camera->GetTransformMatrix()));
    CubeMapShader::SetValue(ShadersType::VertexShader, "view_matrix", &view);

    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
    glPolygonMode(GL_FRONT, GL_FILL);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

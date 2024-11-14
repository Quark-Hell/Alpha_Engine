#include "OpaqueShader.h"

#include <iostream>

#include <Core/Object.h>
#include <Core/World.h>
#include <GLEW/glew.h>

#include <Render/WinManager/AnomalyEngine/Components/Material.h>
#include <Render/WinManager/AnomalyEngine/Components/Mesh.h>

#include "Render/WinManager/AnomalyEngine/Components/Camera.h"
#include "Render/WinManager/AnomalyEngine/Textures/TextureLoader.h"

#include "Render/WinManager/AnomalyEngine/Components/DirectLight.h"

#include "Core/Timer.h"

#include <glm/gtc/type_ptr.hpp>


namespace Render::AnomalyEngine::Shaders {

    OpaqueShader::OpaqueShader(Material *parentMat) : ShaderProgram(parentMat) {
        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/OpaqueShader/VertexShader.txt)", ShadersType::VertexShader);
        AddShaderSource(R"(/ALPHA_Engine/Engine_Assets/Shaders/OpaqueShader/FragmentShader.txt)", ShadersType::FragmentShader);

        OpaqueShader::LoadTextures();

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            std::cout << "Error: Opaque shader was not be created" << std::endl;
        }

        std::cout << "Info: Opaque shader was be created" << std::endl;
    }

    void OpaqueShader::LoadTextures(
        const std::string& diffusePath,
        const std::string& metallicPath,
        const std::string& specularPath,
        const std::string& roughnessPath,
        const std::string& anisotropicPath,
        const std::string& emissionPath,
        const std::string& normalMapPath,
        const std::string& opacityMapPath,
        const std::string& occlusionMapPath) {

        {
            Core::ScopedTimer timer("Info: Load time");

            const auto loader = Textures::TextureLoader::GetInstance();
            if (!diffusePath.empty()) {
                loader->AddTask(_textures[0], diffusePath);
            }
            else {
                loader->AddTask(_textures[0], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!metallicPath.empty()) {
                loader->AddTask(_textures[1], metallicPath);
            }
            else {
                loader->AddTask(_textures[1], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!specularPath.empty()) {
                loader->AddTask(_textures[2], specularPath);
            }
            else {
                loader->AddTask(_textures[2], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!roughnessPath.empty()) {
                loader->AddTask(_textures[3], roughnessPath);
            }
            else {
                loader->AddTask(_textures[3], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!anisotropicPath.empty()) {
                loader->AddTask(_textures[4], anisotropicPath);
            }
            else {
                loader->AddTask(_textures[4], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!emissionPath.empty()) {
                loader->AddTask(_textures[5], emissionPath);
            }
            else {
                loader->AddTask(_textures[5], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyEmission.png)");
            }

            if (!normalMapPath.empty()) {
                loader->AddTask(_textures[6], normalMapPath);
            }
            else {
                loader->AddTask(_textures[6], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!opacityMapPath.empty()) {
                loader->AddTask(_textures[7], opacityMapPath);
            }
            else {
                loader->AddTask(_textures[7], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!occlusionMapPath.empty()) {
                loader->AddTask(_textures[8], occlusionMapPath);
            }
            else {
                loader->AddTask(_textures[8], R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)");
            }

            loader->DoWork();
        }

        TransferTexturesToGPU();
    }

    bool OpaqueShader::TransferTexturesToGPU() {
        for (auto& it : _textures) {
            it.DeleteTextureFromVRAM();
        }

        auto genPar = [](const unsigned int id) {
            glBindTexture(GL_TEXTURE_2D, id);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindTexture(GL_TEXTURE_2D, 0);
        };

        for (auto & texture : _textures) {
            if (texture.GetHeight() == 0)
                continue;

            if (texture.TransferToGPU(true, Textures::EnumTypeOfTexture::Texture2D)) {
                genPar(texture.GetTextureId());
                continue;
            }

            for (auto& it : _textures) {
                it.DeleteTextureFromVRAM();
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            return false;
        }

        for (auto& texture : _textures) {
            texture.DeleteTextureFromRAM();
        }

        return true;
    }

    void OpaqueShader::ApplyShadersSettings(Render::AnomalyEngine::Components::Camera *camera) {
        auto modelMat = glm::mat4(glm::mat3(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
        SetValue(UniformType::mat4x4,"model_matrix", &modelMat);

        auto transMat = glm::transpose(glm::inverse(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
        SetValue(UniformType::mat4x4,"trans_model_mat", &transMat);

        auto MVP = camera->GetProjectionMatrix() * camera->GetParentObject()->GetTransformMatrix() * GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();
        SetValue(UniformType::mat4x4,"MVP", &MVP);

        size_t directLightsCount = Core::World::GetDirLights()->size();
        size_t pointLightsCount = 0;
        size_t spotLightsCount = 0;

//        for (const auto& it : *Core::World::GetDirLights()) {
//            auto* dirLight = static_cast<Components::DirectLight*>(it.get());
//
//            Core::Vector3 direction = dirLight->GetDirection();
//
//            SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].direction"), &direction);
//            SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].color"), &dirLight->color);
//            SetValue(UniformType::floatType,std::string("directLights[").append(std::to_string(directLightsCount)).append("].strength"), &dirLight->intensity);
//        }

        //float ambStrength = 0.2f;
        //SetValue(UniformType::floatType,"ambientStrength", &ambStrength);

//        SetValue(UniformType::integer,"DirectLightsCount", &directLightsCount);
//        SetValue(UniformType::integer,"PointLightsCount", &pointLightsCount);
//        SetValue(UniformType::integer,"SpotLightsCount", &spotLightsCount);

        //Core::Vector3 pos = camera->GetParentObject()->transform.GetPosition();
        //SetValue(UniformType::vec3,"viewPos", &pos);

        _textures[0].BindTexture(0, OpaqueShader::GetProgramId(), "diffuseMap");
//        //_textures[1].BindTexture(1, OpaqueShader::GetProgramId(), "metallicMap");
//        //_textures[2].BindTexture(2, OpaqueShader::GetProgramId(), "specularMap");
//        //_textures[3].BindTexture(3, OpaqueShader::GetProgramId(), "roughnessMap");
//        //_textures[4].BindTexture(4, OpaqueShader::GetProgramId(), "anisotropicMap");
//        _textures[5].BindTexture(5, OpaqueShader::GetProgramId(), "emissionMap");
//        //_textures[6].BindTexture(6, OpaqueShader::GetProgramId(), "normalMap");
//        //_textures[7].BindTexture(7, OpaqueShader::GetProgramId(), "opacityMap");
//        //_textures[8].BindTexture(8, OpaqueShader::GetProgramId(), "occlusionMap");

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}
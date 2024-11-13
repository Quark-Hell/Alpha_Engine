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

        OpaqueShader::LoadTextures(
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyEmission.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)",
            R"(/ALPHA_Engine/Engine_Assets/Textures/EmptyTexture.png)"
            );

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
            if (!diffusePath.empty())
                loader->AddTask(_textures[0], diffusePath);
            if (!metallicPath.empty())
                loader->AddTask(_textures[1], metallicPath);
            if (!specularPath.empty())
                loader->AddTask(_textures[2], specularPath);
            if (!roughnessPath.empty())
                loader->AddTask(_textures[3], roughnessPath);
            if (!anisotropicPath.empty())
                loader->AddTask(_textures[4], anisotropicPath);
            if (!emissionPath.empty())
                loader->AddTask(_textures[5], emissionPath);
            if (!normalMapPath.empty())
                loader->AddTask(_textures[6], normalMapPath);
            if (!opacityMapPath.empty())
                loader->AddTask(_textures[7], opacityMapPath);
            if (!occlusionMapPath.empty())
                loader->AddTask(_textures[8], occlusionMapPath);


            loader->DoWork();
        }

        TransferTexturesToGPU();
    }

    bool OpaqueShader::TransferTexturesToGPU() {
        for (auto& it : _textures) {
            it.DeleteTextureFromVRAM();
        }

        auto genPar = []() {
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindTexture(GL_TEXTURE_2D, 0);
        };

        for (auto & _texture : _textures) {
            if (_texture.GetHeight() == 0)
                continue;

            if (_texture.TransferToGPU(true, Textures::EnumTypeOfTexture::Texture2D)) {
                genPar();
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

        unsigned int id = OpaqueShader::GetProgramId();
        unsigned int transformLoc = glGetUniformLocation(id, "transform");

        glm::mat4 trans = glm::mat4(1.0f);
        //trans = GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();

        trans = glm::translate(trans, glm::vec3(0,0,5));
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(2, 2, 2));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glPolygonMode(GL_FRONT, GL_FILL);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);

//        size_t directLightsCount = Core::World::GetDirLights()->size();
//        size_t pointLightsCount = 0;
//        size_t spotLightsCount = 0;
//
//        for (const auto& it : *Core::World::GetDirLights()) {
//            auto* dirLight = static_cast<Components::DirectLight*>(it.get());
//
//            Core::Vector3 direction = dirLight->GetDirection();
//
//            SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].direction"), &direction);
//            SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].color"), &dirLight->color);
//            SetValue(UniformType::floatType,std::string("directLights[").append(std::to_string(directLightsCount)).append("].strength"), &dirLight->intensity);
//        }
//
//        float ambStrength = 0.2f;
//        SetValue(UniformType::floatType,"ambientStrength", &ambStrength);
//
//        SetValue(UniformType::integer,"DirectLightsCount", &directLightsCount);
//        SetValue(UniformType::integer,"PointLightsCount", &pointLightsCount);
//        SetValue(UniformType::integer,"SpotLightsCount", &spotLightsCount);
//
//        Core::Vector3 pos = camera->GetParentObject()->transform.GetPosition();
//        SetValue(UniformType::vec3,"viewPos", &pos);
//
//        glBindTexture(GL_TEXTURE0, _textures[0].GetTextureId());
//        glBindTexture(GL_TEXTURE5, _textures[0].GetTextureId());
//
//        //_textures[0].BindTexture(0, OpaqueShader::GetProgramId(), "diffuseMap");
//        //_textures[1].BindTexture(1, OpaqueShader::GetProgramId(), "metallicMap");
//        //_textures[2].BindTexture(2, OpaqueShader::GetProgramId(), "specularMap");
//        //_textures[3].BindTexture(3, OpaqueShader::GetProgramId(), "roughnessMap");
//        //_textures[4].BindTexture(4, OpaqueShader::GetProgramId(), "anisotropicMap");
//        //_textures[5].BindTexture(5, OpaqueShader::GetProgramId(), "emissionMap");
//        //_textures[6].BindTexture(6, OpaqueShader::GetProgramId(), "normalMap");
//        //_textures[7].BindTexture(7, OpaqueShader::GetProgramId(), "opacityMap");
//        //_textures[8].BindTexture(8, OpaqueShader::GetProgramId(), "occlusionMap");
//
//        auto modelMat = glm::mat4(glm::mat3(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
//        SetValue(UniformType::mat4x4,"model_matrix", &modelMat);
//
//        auto transMat = glm::transpose(glm::inverse(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
//        SetValue(UniformType::mat4x4,"trans_model_mat", &transMat);
//
//        auto t = GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();
//        glm::translate(t, glm::vec3(0,0,5));
//
//        auto MVP = camera->GetProjectionMatrix() * camera->GetParentObject()->GetTransformMatrix() * t;
//        SetValue(UniformType::mat4x4,"MVP", &MVP);
//
//        //glPolygonMode(GL_FRONT, GL_FILL);
//        //glEnable(GL_CULL_FACE);
//        //glEnable(GL_DEPTH_TEST);
//        //glDepthFunc(GL_LEQUAL);
    }
}
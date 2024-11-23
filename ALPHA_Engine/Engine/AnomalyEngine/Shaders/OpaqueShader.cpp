#include "OpaqueShader.h"

#include "AnomalyEngine/Buffers/DirectLightsBuffer.h"
#include "AnomalyEngine/Buffers/PointLightsBuffer.h"

#include "AnomalyEngine/Components/DirectLight.h"
#include "AnomalyEngine/Components/PointLight.h"

#include "Core/Logger/Logger.h"

#include <Core/Object.h>
#include <Core/World.h>
#include <GLEW/glew.h>

#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Textures/TextureLoader.h"

#include <glm/gtc/type_ptr.hpp>

#include "Core/ECS/TSystemData.h"


namespace AnomalyEngine {

    OpaqueShader::OpaqueShader(Material *parentMat) : ShaderProgram(parentMat) {
        AddShaderSource(R"(/Engine_Assets/Shaders/OpaqueShader/VertexShader.glsl)", ShadersType::VertexShader);
        AddShaderSource(R"(/Engine_Assets/Shaders/OpaqueShader/FragmentShader.glsl)", ShadersType::FragmentShader);

        OpaqueShader::LoadTextures();

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            Core::Logger::LogError("Opaque shader was not be created: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        Core::Logger::LogInfo("Opaque shader was be created");
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
            Core::ScopedTimer timer("Load time");

            const auto loader = TextureLoader::GetInstance();
            if (!diffusePath.empty()) {
                loader->AddTask(_textures[0], diffusePath);
            }
            else {
                loader->AddTask(_textures[0], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!metallicPath.empty()) {
                loader->AddTask(_textures[1], metallicPath);
            }
            else {
                loader->AddTask(_textures[1], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!specularPath.empty()) {
                loader->AddTask(_textures[2], specularPath);
            }
            else {
                loader->AddTask(_textures[2], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!roughnessPath.empty()) {
                loader->AddTask(_textures[3], roughnessPath);
            }
            else {
                loader->AddTask(_textures[3], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!anisotropicPath.empty()) {
                loader->AddTask(_textures[4], anisotropicPath);
            }
            else {
                loader->AddTask(_textures[4], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!emissionPath.empty()) {
                loader->AddTask(_textures[5], emissionPath);
            }
            else {
                loader->AddTask(_textures[5], R"(/Engine_Assets/Textures/EmptyEmission.png)");
            }

            if (!normalMapPath.empty()) {
                loader->AddTask(_textures[6], normalMapPath);
            }
            else {
                loader->AddTask(_textures[6], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!opacityMapPath.empty()) {
                loader->AddTask(_textures[7], opacityMapPath);
            }
            else {
                loader->AddTask(_textures[7], R"(/Engine_Assets/Textures/EmptyTexture.png)");
            }

            if (!occlusionMapPath.empty()) {
                loader->AddTask(_textures[8], occlusionMapPath);
            }
            else {
                loader->AddTask(_textures[8], R"(/Engine_Assets/Textures/EmptyTexture.png)");
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

            if (texture.TransferToGPU(true, EnumTypeOfTexture::Texture2D)) {
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

    void OpaqueShader::ApplyShadersSettings(Camera &camera) {
        if (camera.GetParentObject() == nullptr) {
            Core::Logger::LogError("Camera parent object was null: " + __LOGERROR__);
            return;
        }

        //=============================================Object Matrices=============================================//
        auto modelMat = glm::mat4(glm::mat3(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
        SetValue(UniformType::mat4x4,"model_matrix", &modelMat);

        auto transMat = glm::mat3(glm::transpose(glm::inverse(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix())));
        SetValue(UniformType::mat3x3,"trans_model_mat", &transMat);

        auto MVP = camera.GetProjectionMatrix() * camera.GetParentObject()->GetTransformMatrix() * GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();
        SetValue(UniformType::mat4x4,"MVP", &MVP);
        //=============================================Object Matrices=============================================//



        //=============================================Ambient Light=============================================//
        float ambStrength = Core::World::GetWorldAmbient();
        SetValue(UniformType::floatType,"ambientStrength", &ambStrength);
        //=============================================Ambient Light=============================================//



        //=============================================Direct Light=============================================//
        size_t directLightsCount = 0;
        auto directLightsBuffer = reinterpret_cast<DirectLightsBuffer*>(Core::World::GetSystemData("DirectLightsBuffer"));

        if (!directLightsBuffer->GetAllData().empty()) {
            for (size_t i = 0; i < directLightsBuffer->GetAllData().size(); i++) {
                auto dirLight = directLightsBuffer->GetData(i);

                Core::Vector3 direction = dirLight.GetDirection();

                SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].direction"), &direction);
                SetValue(UniformType::vec3,std::string("directLights[").append(std::to_string(directLightsCount)).append("].color"), &dirLight.Color);
                SetValue(UniformType::floatType,std::string("directLights[").append(std::to_string(directLightsCount)).append("].strength"), &dirLight.Intensity);

                directLightsCount++;
            }
        }
        SetValue(UniformType::integer,"DirectLightsCount", &directLightsCount);
        //=============================================Direct Light=============================================//



        //=============================================Point Light=============================================//
        size_t pointLightsCount = 0;
        auto pointLightsBuffer = reinterpret_cast<PointLightsBuffer*>(Core::World::GetSystemData("PointLightsBuffer"));

        if (!pointLightsBuffer->GetAllData().empty()) {
            for (size_t i = 0; i < pointLightsBuffer->GetAllData().size(); i++) {
                auto pLight = pointLightsBuffer->GetData(i);

                Core::Vector3 pos = pLight.GetParentObject()->transform.GetPosition();

                SetValue(UniformType::vec3, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].position"), &pos);
                SetValue(UniformType::vec3, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].color"), &pLight.Color);
                SetValue(UniformType::floatType, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].radius"), &pLight.Radius);
                SetValue(UniformType::floatType, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].strength"), &pLight.Intensity);

                SetValue(UniformType::floatType, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].constant"), &pLight.Constant);
                SetValue(UniformType::floatType, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].linear"), &pLight.Linear);
                SetValue(UniformType::floatType, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].quadratic"), &pLight.Quadratic);

                pointLightsCount++;
            }
        }
        SetValue(UniformType::integer,"PointLightsCount", &pointLightsCount);
        //=============================================Point Light=============================================//

        size_t spotLightsCount = 0;

//        SetValue(UniformType::integer,"SpotLightsCount", &spotLightsCount);

        Core::Vector3 pos = camera.GetParentObject()->transform.GetPosition();
        SetValue(UniformType::vec3,"viewPos", &pos);

        //=============================================Bind Textures=============================================//
        _textures[0].BindTexture(0, OpaqueShader::GetProgramId(), "diffuseMap");
//        //_textures[1].BindTexture(1, OpaqueShader::GetProgramId(), "metallicMap");
//        //_textures[2].BindTexture(2, OpaqueShader::GetProgramId(), "specularMap");
//        //_textures[3].BindTexture(3, OpaqueShader::GetProgramId(), "roughnessMap");
//        //_textures[4].BindTexture(4, OpaqueShader::GetProgramId(), "anisotropicMap");
        _textures[5].BindTexture(1, OpaqueShader::GetProgramId(), "emissionMap");
//        //_textures[6].BindTexture(6, OpaqueShader::GetProgramId(), "normalMap");
//        //_textures[7].BindTexture(7, OpaqueShader::GetProgramId(), "opacityMap");
//        //_textures[8].BindTexture(8, OpaqueShader::GetProgramId(), "occlusionMap");
        //=============================================Bind Textures=============================================//

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}

#include "OpaqueShader.h"

#include "AnomalyEngine/Buffers/DirectLightsBuffer.h"
#include "AnomalyEngine/Buffers/PointLightsBuffer.h"

#include "AnomalyEngine/Components/DirectLight.h"
#include "AnomalyEngine/Components/PointLight.h"

#include <glad/glad.h>

#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Textures/TextureLoader.h"

#include "Core/ECS/TSystemData.h"
#include "Core/Logger/Logger.h"
#include <Core/Objects/GameObject.h>
#include <Core/World.h>

#include <glm/gtc/type_ptr.hpp>

namespace AnomalyEngine {

    OpaqueShader::OpaqueShader(Material* parentMat) : ShaderProgram(parentMat) {
        AddShaderSource(R"(/Assets/Shaders/OpaqueShader/VertexShader.glsl)", ShadersType::VertexShader);
        AddShaderSource(R"(/Assets/Shaders/OpaqueShader/FragmentShader.glsl)", ShadersType::FragmentShader);

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
                    loader->AddTask(_textures[0], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!metallicPath.empty()) {
                    loader->AddTask(_textures[1], metallicPath);
                }
                else {
                    loader->AddTask(_textures[1], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!specularPath.empty()) {
                    loader->AddTask(_textures[2], specularPath);
                }
                else {
                    loader->AddTask(_textures[2], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!roughnessPath.empty()) {
                    loader->AddTask(_textures[3], roughnessPath);
                }
                else {
                    loader->AddTask(_textures[3], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!anisotropicPath.empty()) {
                    loader->AddTask(_textures[4], anisotropicPath);
                }
                else {
                    loader->AddTask(_textures[4], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!emissionPath.empty()) {
                    loader->AddTask(_textures[5], emissionPath);
                }
                else {
                    loader->AddTask(_textures[5], R"(/Assets/Textures/EmptyEmission.png)");
                }

                if (!normalMapPath.empty()) {
                    loader->AddTask(_textures[6], normalMapPath);
                }
                else {
                    loader->AddTask(_textures[6], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!opacityMapPath.empty()) {
                    loader->AddTask(_textures[7], opacityMapPath);
                }
                else {
                    loader->AddTask(_textures[7], R"(/Assets/Textures/EmptyTexture.png)");
                }

                if (!occlusionMapPath.empty()) {
                    loader->AddTask(_textures[8], occlusionMapPath);
                }
                else {
                    loader->AddTask(_textures[8], R"(/Assets/Textures/EmptyTexture.png)");
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

        for (auto& texture : _textures) {
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

    void OpaqueShader::ApplyShadersSettings(Camera& camera, int parentIndex) {
        if (camera.GetParentObject() == nullptr) {
            Core::Logger::LogError("Camera parent object was null: " + __LOGERROR__);
            return;
        }

        Core::Object* parent;

        if (parentIndex == -1) {
            parent = GetParentMaterial()->GetParentMesh()->GetParentObject();
        }
        else {
            auto parentsObj = GetParentMaterial()->GetParentMesh()->GetParentsObject();
            parent = parentsObj[parentIndex];
        }

        //=============================================Object Matrices=============================================//
        auto modelMat = glm::mat4(glm::mat3(parent->transform.GetTransformMatrix()));
        SetValue("model_matrix", &modelMat);

        auto transMat = glm::mat3(glm::transpose(glm::inverse(parent->transform.GetTransformMatrix())));
        SetValue("trans_model_mat", &transMat);

        auto MVP = camera.GetProjectionMatrix() * camera.GetParentObject()->transform.GetTransformMatrix() * parent->transform.GetTransformMatrix();
        SetValue("MVP", &MVP);
        //=============================================Object Matrices=============================================//

        //=============================================Ambient Light=============================================//
        float ambStrength = Core::World::GetWorldAmbient();
        SetValue("ambientStrength", &ambStrength);
        //=============================================Ambient Light=============================================//



        //=============================================Direct Light=============================================//
        int directLightsCount = 0;
        auto directLightsBuffer = Core::World::GetSystemData<DirectLightsBuffer>("DirectLightsBuffer");

        if (!directLightsBuffer->GetAllData().empty()) {
            for (size_t i = 0; i < directLightsBuffer->GetAllData().size(); i++) {
                auto& dirLight = directLightsBuffer->GetData(i);

                glm::vec3 direction = dirLight.GetDirection();

                SetValue(std::string("directLights[").append(std::to_string(directLightsCount)).append("].direction"), &direction);
                SetValue(std::string("directLights[").append(std::to_string(directLightsCount)).append("].color"), &dirLight.Color);
                SetValue(std::string("directLights[").append(std::to_string(directLightsCount)).append("].strength"), &dirLight.Intensity);

                directLightsCount++;
            }
        }
        SetValue("DirectLightsCount", &directLightsCount);
        //=============================================Direct Light=============================================//



        //=============================================Point Light=============================================//
        int pointLightsCount = 0;
        auto pointLightsBuffer = Core::World::GetSystemData<PointLightsBuffer>("PointLightsBuffer");

        if (!pointLightsBuffer->GetAllData().empty()) {
            for (size_t i = 0; i < pointLightsBuffer->GetAllData().size(); i++) {
                auto& pLight = pointLightsBuffer->GetData(i);

                glm::vec3 pos = glm::vec3(
                    pLight.GetParentObject()->transform.GetPosition().x,
                    pLight.GetParentObject()->transform.GetPosition().y,
                    pLight.GetParentObject()->transform.GetPosition().z);

                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].position"), &pos);
                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].color"), &pLight.Color);
                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].radius"), &pLight.Radius);
                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].strength"), &pLight.Intensity);

                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].constant"), &pLight.Constant);
                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].linear"), &pLight.Linear);
                SetValue(std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].quadratic"), &pLight.Quadratic);

                pointLightsCount++;
            }
        }
        SetValue("PointLightsCount", &pointLightsCount);
        //=============================================Point Light=============================================//

        size_t spotLightsCount = 0;

        //        SetValue(UniformType::integer,"SpotLightsCount", &spotLightsCount);

        glm::vec3 pos = glm::vec3(
            camera.GetParentObject()->transform.GetPosition().x,
            camera.GetParentObject()->transform.GetPosition().y,
            camera.GetParentObject()->transform.GetPosition().z);
        SetValue("viewPos", &pos);

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

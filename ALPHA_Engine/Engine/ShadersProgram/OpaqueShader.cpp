#include "OpaqueShader.h"

#include "World.h"

#include "Modules/Light/Light.h"
#include "Modules/Light/DirectLight.h"
#include "Modules/Light/PointLight.h"
#include "Modules/Light/SpotLight.h"

#include "Modules/Mesh.h"

OpaqueShader::OpaqueShader(Material* parentMat) : ShaderProgram(parentMat)
{
    OpaqueShader::LoadTexture(Diffuse, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(Metallic, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(Specular, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(Roughness, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(Anisotropic, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(Emission, "\\Textures\\EmptyEmission.png");
    OpaqueShader::LoadTexture(NormalsMap, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(OpacityMap, "\\Textures\\EmptyTexture.png");
    OpaqueShader::LoadTexture(OcclusionMap, "\\Textures\\EmptyTexture.png");


    OpaqueShader::CreateShader("\\Shaders\\BaseVertexShaders\\VertexShader.txt", ShadersType::VertexShader);
    OpaqueShader::CreateShader("\\Shaders\\BaseFragmentShaders\\FragmentShader.txt", ShadersType::FragmentShader);

    OpaqueShader::InitShader();
}

OpaqueShader::~OpaqueShader()
{
}

bool OpaqueShader::LoadTexture(
    std::string diffusePath,
    std::string metallicPath,
    std::string specularPath,
    std::string roughnessPath,
    std::string anisotropicPath,
    std::string emissionPath,
    std::string normalsPath,
    std::string opacityPath,
    std::string occlusionPath) {

    auto genPar = []() {
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        };

    if(diffusePath != "")
        TextureLoader::AddTask(_diffuse, diffusePath);
    if (metallicPath != "")
        TextureLoader::AddTask(_metallic, metallicPath);
    if (specularPath != "")
        TextureLoader::AddTask(_specular, specularPath);
    if (roughnessPath != "")
        TextureLoader::AddTask(_roughness, roughnessPath);
    if (anisotropicPath != "")
        TextureLoader::AddTask(_anisotropic, anisotropicPath);
    if (emissionPath != "")
        TextureLoader::AddTask(_emission, emissionPath);
    if (normalsPath != "")
        TextureLoader::AddTask(_normalsMap, normalsPath);
    if (opacityPath != "")
        TextureLoader::AddTask(_opacityMap, opacityPath);
    if (occlusionPath != "")
        TextureLoader::AddTask(_occlusionMap, occlusionPath);

    TextureLoader::DoWork();

    if (OpaqueShader::_diffuse.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_metallic.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_specular.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_roughness.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_anisotropic.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_emission.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_normalsMap.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_opacityMap.TransferToGPU(true, false))
        genPar();
    if (OpaqueShader::_occlusionMap.TransferToGPU(true, false))
        genPar();

    return true;
}

bool OpaqueShader::LoadTexture(TypeOfOpaqueTextuere typeOfTexture, std::string pathToTexture)
{
    auto genPar = []() {
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        };

    switch (typeOfTexture)
    {
    case Diffuse:
        OpaqueShader::_diffuse.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_diffuse.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case Metallic:
        OpaqueShader::_metallic.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_metallic.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case Specular:
        OpaqueShader::_specular.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_specular.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case Roughness:
        OpaqueShader::_roughness.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_roughness.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case Anisotropic:
        OpaqueShader::_anisotropic.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_anisotropic.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case Emission:
        OpaqueShader::_emission.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_emission.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case NormalsMap:
        OpaqueShader::_normalsMap.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_normalsMap.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case OpacityMap:
        OpaqueShader::_opacityMap.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_opacityMap.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    case OcclusionMap:
        OpaqueShader::_occlusionMap.CreateTexture(pathToTexture.c_str());
        if (!OpaqueShader::_occlusionMap.TransferToGPU(true, false))
            return false;
        genPar();
        break;
    default:
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    return true;
}

void OpaqueShader::ApplyShadersSettings(std::shared_ptr<Camera> camera)
{
	int ambientLightsCount = 0;
	int directLightsCount = 0;
	int pointLightsCount = 0;
	int spotLightsCount = 0;

	for (int i = 0; i < World::LightsOnScene.size(); i++) {
    
		ModulesList type = World::LightsOnScene[i]->GetType();
    
		if (type == ModulesList::DirectLightType) {
			auto light = (DirectLight*)(World::LightsOnScene[i]);
            
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(directLightsCount)).append("].direction"), light->GetDirection());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(directLightsCount)).append("].color"), light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(directLightsCount)).append("].strength"), light->strength);
    
			directLightsCount++;
			continue;
		}
		if (type == ModulesList::PointLightType) {
            PointLight* light = (PointLight*)(World::LightsOnScene[i]);
            
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].position"), light->GetPosition());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].color"), light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].radius"), light->radius);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].strength"), light->strength);
            
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].constant"), light->constant);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].linear"), light->linear);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(pointLightsCount)).append("].quadratic"), light->quadratic);
    
			pointLightsCount++;
			continue;
		}
		if (type == ModulesList::SpotLightType) {
			auto light = (SpotLight*)(World::LightsOnScene[i]);
            
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].direction"), light->GetDirection());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].position"), light->GetPosition());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].color"), light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].strength"), light->strength);
            
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].cutOff"), light->CutOff);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(spotLightsCount)).append("].outerCutOff"), light->OuterCutOff);
    
			spotLightsCount++;
			continue;
		}
	}

	directLightsCount = Math::Clamp(0, 16, directLightsCount);
	pointLightsCount = Math::Clamp(0, 16, pointLightsCount);
	spotLightsCount = Math::Clamp(0, 16, spotLightsCount);

	ShaderProgram::SetValue(ShadersType::FragmentShader, "ambientStrength", &World::WorldAmbientStrength);

	ShaderProgram::SetValue(ShadersType::FragmentShader, "DirectLightsCount", &directLightsCount);
	ShaderProgram::SetValue(ShadersType::FragmentShader, "PointLightsCount", &pointLightsCount);
	ShaderProgram::SetValue(ShadersType::FragmentShader, "SpotLightsCount", &spotLightsCount);


	ShaderProgram::SetValue(ShadersType::FragmentShader, "viewPos", camera->GetPosition());

	_diffuse.BindTexture(0, OpaqueShader::GetProgramId(), "diffuseMap");
	//_metallic.BindTexture(1, OpaqueShader::GetProgramId(), "diffuseMap");
	//_specular.BindTexture(2, OpaqueShader::GetProgramId(), "diffuseMap");
	//_roughness.BindTexture(3, OpaqueShader::GetProgramId(), "diffuseMap");
	//_anisotropic.BindTexture(4, OpaqueShader::GetProgramId(), "diffuseMap");
	_emission.BindTexture(5, OpaqueShader::GetProgramId(), "emissionMap");
	//_normalsMap.BindTexture(6, OpaqueShader::GetProgramId(), "diffuseMap");
	//_opacityMap.BindTexture(7, OpaqueShader::GetProgramId(), "diffuseMap");
	//_occlusionMap.BindTexture(8, OpaqueShader::GetProgramId(), "diffuseMap");

    glm::mat4x4 modelMat = OpaqueShader::GetParentMaterial()->GetParentMesh()->GetTransformMatrix();
	OpaqueShader::GetParentMaterial()->Shader->SetValue(ShadersType::VertexShader, "model_matrix", &modelMat);

	glm::mat3x3 transMat = glm::transpose(glm::inverse(OpaqueShader::GetParentMaterial()->GetParentMesh()->GetTransformMatrix()));
	OpaqueShader::GetParentMaterial()->Shader->SetValue(ShadersType::VertexShader, "trans_model_mat", &transMat);

	glm::mat4x4 MVP = camera->GetProjectionMatrix() * camera->GetTransformMatrix() * OpaqueShader::GetParentMaterial()->GetParentMesh()->GetTransformMatrix();
	OpaqueShader::GetParentMaterial()->Shader->SetValue(ShadersType::VertexShader, "MVP", &(MVP));
}

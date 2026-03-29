#include "WireframeShader.h"

#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "Core/Math/glmMath.h"
#include "Core/Objects/GameObject.h"

namespace AnomalyEngine {
	WireframeShader::WireframeShader(Material* parentMat) : ShaderProgram(parentMat) {
        AddShaderSource(R"(/Assets/Shaders/WireframeShader/VertexShader.glsl)", ShadersType::VertexShader);
        AddShaderSource(R"(/Assets/Shaders/WireframeShader/FragmentShader.glsl)", ShadersType::FragmentShader);

        SetRenderMode(RenderMode::Lines);

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            Core::Logger::LogError("Wireframe shader was not be created: " + __LOGERROR__);
        }

        Core::Logger::LogInfo("Wireframe shader was be created");
	}

    void WireframeShader::ApplyShadersSettings(Camera& camera) {
        if (camera.GetParentObject() == nullptr) {
            Core::Logger::LogError("Camera parent object was null: " + __LOGERROR__);
            return;
        }

        Core::Object* parent;
        parent = GetParentMaterial()->GetParentMesh()->GetParentObject();


        //=============================================Object Matrices=============================================//
        auto modelMat = glm::mat4(glm::mat3(parent->transform.GetTransformMatrix()));
        SetValue("model_matrix", &modelMat);

        auto transMat = glm::mat3(glm::transpose(glm::inverse(parent->transform.GetTransformMatrix())));
        SetValue("trans_model_mat", &transMat);

        auto MVP = camera.GetProjectionMatrix() * camera.GetParentObject()->transform.GetTransformMatrix() * parent->transform.GetTransformMatrix();
        SetValue("MVP", &MVP);
        //=============================================Object Matrices=============================================//

        glm::vec3 col = {FrameColor.r, FrameColor.g, FrameColor.b};
        SetValue("color", &col);
    }
}
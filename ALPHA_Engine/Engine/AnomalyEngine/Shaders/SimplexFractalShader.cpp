#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "SimplexFractalShader.h"

#include "Core/Logger/Logger.h"
#include "Core/Object.h"

#include <glad/glad.h>
#include <random>
#include <climits>

#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

namespace AnomalyEngine {
    SimplexFractalShader::SimplexFractalShader(Material *parentMat) : ShaderProgram(parentMat) {
        AddShaderSource(R"(/Assets/Shaders/SimplexFractalShader/VertexShader.glsl)", ShadersType::VertexShader);
        AddShaderSource(R"(/Assets/Shaders/SimplexFractalShader/FragmentShader.glsl)", ShadersType::FragmentShader);

        GenerateRandomSeed();

        if (ShaderProgram::CompileShader()) {
            ShaderProgram::AttachShader();
            ShaderProgram::DeleteShader();
        }
        else {
            ShaderProgram::DeleteShader();
            Core::Logger::LogError("Perlin shader was not be created: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        Core::Logger::LogInfo("Perlin shader was be created");
    }

    void SimplexFractalShader::GenerateRandomSeed() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1,SIZE_MAX);

        seed = dist(rng);
    }

    void SimplexFractalShader::ApplyShadersSettings(Camera &camera) {
        if (camera.GetParentObject() == nullptr) {
            Core::Logger::LogError("Camera parent object was null: " + __LOGERROR__);
            return;
        }

        //=============================================Object Matrices=============================================//
        auto MVP = camera.GetProjectionMatrix() * camera.GetParentObject()->GetTransformMatrix() * GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();
        SetValue(UniformType::mat4x4,"MVP", &MVP);

        auto modelMat = glm::mat4(glm::mat3(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
        SetValue(UniformType::mat4x4,"model_matrix", &modelMat);
        //=============================================Object Matrices=============================================//

        seed = glfwGetTime();
        SetValue(UniformType::floatType,"seed", &seed);
        SetValue(UniformType::floatType,"resolution", &resolution);
        SetValue(UniformType::floatType,"intensity",  &intensity);
        SetValue(UniformType::floatType,"minFactor",  &minFactor);
        SetValue(UniformType::floatType,"maxFactor",  &maxFactor);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}
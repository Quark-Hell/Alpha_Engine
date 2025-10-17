#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "SimplexFractalShader.h"

#include "Core/Logger/Logger.h"
#include "Core/Objects/GameObject.h"

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

        Seed = dist(rng);
    }

    void SimplexFractalShader::ApplyShadersSettings(Camera &camera, int parentIndex) {
        if (camera.GetParentObject() == nullptr) {
            Core::Logger::LogError("Camera parent object was null: " + __LOGERROR__);
            return;
        }

        //=============================================Object Matrices=============================================//
        auto MVP = camera.GetProjectionMatrix() * camera.GetParentObject()->transform.GetTransformMatrix() * GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix();
        SetValue("MVP", &MVP);

        auto modelMat = glm::mat4(glm::mat3(GetParentMaterial()->GetParentMesh()->GetParentObject()->transform.GetTransformMatrix()));
        SetValue("model_matrix", &modelMat);
        //=============================================Object Matrices=============================================//

        Seed = glfwGetTime();
        SetValue("seed", &Seed);

        SetValue("resolution", &Resolution);
        SetValue("intensity",  &Intensity);
        SetValue("contrast",   &Contrast);
        SetValue("brightness", &Brightness);

        SetValue("minFactor",  &MinFactor);
        SetValue("maxFactor",  &MaxFactor);

        size_t size = colors.size();
        SetValue("colorCount", &size);

        for (int i = 0; i < size; i++) {
            std::string uniformName = "gradientColors[" + std::to_string(i) + "]";
            glm::vec3 color = glm::vec3(colors[i].r, colors[i].g, colors[i].b);
            SetValue(uniformName, &color);
        }

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}
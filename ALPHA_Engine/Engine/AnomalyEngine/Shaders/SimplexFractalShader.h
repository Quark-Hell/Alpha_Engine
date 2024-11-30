#pragma once
#include "AnomalyEngine/Shaders/ShaderProgram.h"

namespace AnomalyEngine {
    class SimplexFractalShader final : public ShaderProgram {
        friend class RenderEngine;
        friend class Material;

    public:
        float seed;
        float resolution = 4;
        float intensity = 2.5;
        float minFactor = 0;
        float maxFactor = 1.5;

    private:
        bool TransferTexturesToGPU();

        void ApplyShadersSettings(Camera &camera) override;

    public:
        SimplexFractalShader(Material *parentMat);

        ~SimplexFractalShader() override = default;

        void GenerateRandomSeed();
    };
}

#pragma once
#include "AnomalyEngine/Shaders/ShaderProgram.h"
#include "AnomalyEngine/Utility/Color.h"

namespace AnomalyEngine {
    class SimplexFractalShader final : public ShaderProgram {
        friend class RenderEngine;
        friend class Material;

    public:
        float Seed;
        float Resolution = 4;
        float Intensity = 1;
        float Contrast = 1;
        float Brightness = 0;
        float MinFactor = 0;
        float MaxFactor = 0.5;

        std::vector<Color> colors;


    private:
        bool TransferTexturesToGPU();

        void ApplyShadersSettings(Camera &camera) override;

    public:
        SimplexFractalShader(Material *parentMat);

        ~SimplexFractalShader() override = default;

        void GenerateRandomSeed();
    };
}

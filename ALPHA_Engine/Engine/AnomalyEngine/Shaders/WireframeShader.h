#pragma once

#include "ShaderProgram.h"
#include "AnomalyEngine/Utility/Color.h"


namespace AnomalyEngine {
    class Material;

    class WireframeShader final : public ShaderProgram {
    public:
        AnomalyEngine::Color FrameColor = Color::Green;

    public:
        WireframeShader(Material* parentMat);
        ~WireframeShader() override = default;

        void ApplyShadersSettings(Camera& camera) override;
    };
}
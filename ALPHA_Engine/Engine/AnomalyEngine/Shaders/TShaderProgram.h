#pragma once

#include <iostream>

#include "AnomalyEngine/Shaders/ShaderProgram.h"

namespace AnomalyEngine {
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<ShaderProgram,T>, bool>>
    class TShaderProgram : public ShaderProgram {
    public:
    //protected:
        TShaderProgram(Material *parentMat) : ShaderProgram(parentMat) {}
    public:
        ~TShaderProgram() override = default;
        virtual T* GetShader() = 0;
        //void GetShader() {
        //    std::cout << "test";
        //}
    };
}
//#include "AnomalyEngine/Shaders/ShaderProgram.h"
//
//namespace AnomalyEngine {
//    template<typename T, typename = std::enable_if_t<std::is_convertible_v<ShaderProgram, T>>>
//    class TShaderProgram : public ShaderProgram {
//    protected:
//        TShaderProgram(Material *parentMat);
//
//    public:
//        ~TShaderProgram() override = default;
//
//        T& GetShader() {
//            return this;
//        }
//
//    };
//}
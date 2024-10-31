#pragma once
#include "BaseTexture.h"

namespace Render::AnomalyEngine::Textures {

    enum EnumTypeOfTexture : unsigned short {
        Texture2D = 0,
        TEXTURE_CUBE_MAP_POSITIVE_X = 1,
        TEXTURE_CUBE_MAP_NEGATIVE_X = 2,
        TEXTURE_CUBE_MAP_POSITIVE_Y = 3,
        TEXTURE_CUBE_MAP_NEGATIVE_Y = 4,
        TEXTURE_CUBE_MAP_POSITIVE_Z = 5,
        TEXTURE_CUBE_MAP_NEGATIVE_Z = 6
    };

    class OpenGLTexture : public BaseTexture {
        public:
        OpenGLTexture();
        ~OpenGLTexture() override;

        bool TransferToGPU(
        bool genTextureAuto,
        bool unbindTextureAuto,
        EnumTypeOfTexture typeOfTexture) override;

        bool BindTexture(unsigned int index, unsigned int programId, std::string samplerName) override;
    };

}
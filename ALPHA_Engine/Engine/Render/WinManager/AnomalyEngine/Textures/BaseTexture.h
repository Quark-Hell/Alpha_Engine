#pragma once

#include <string>
#include <memory>

namespace Render::AnomalyEngine::Textures {
    enum EnumTypeOfWrapping {
        Repeat = 0,
        MirroredRepeat = 1,
        ClampToEdge = 2,
        ClampToBorder = 3
    };

    enum EnumTypeOfTextureFiltering {
        Linear = 0,
        Nearest = 1
    };

    enum EnumTypeOfMIPMAP {
        NearestMipmapNearest = 0,
        LinearMipmapNearest = 1,
        NearestMipmapLinear = 2,
        LinearMipmapLinear = 3
    };

    enum EnumTypeOfTexture : unsigned short;

    //enum TypeOfOpaqueTexture  : unsigned short {
    //    Diffuse = 0,
    //    Metallic = 1,
    //    Specular = 2,
    //    Roughness = 3,
    //    Anisotropic = 4,
    //    Emission = 5,
    //    NormalsMap = 6,
    //    OpacityMap = 7,
    //    OcclusionMap = 8
    //};

    class BaseTexture {
    protected:
        std::unique_ptr<unsigned char> _textureData = std::unique_ptr<unsigned char>();

        unsigned int _width = 0;
        unsigned int _height = 0;
        unsigned int _channelsCount = 0;

        unsigned int textureId = 0;
        unsigned int textureLocation = 0;

        //Other representation(DirectX, Vulkan...)

        EnumTypeOfWrapping _typeOfWrapping;
        EnumTypeOfTextureFiltering _typeOfTextureFiltering;
        EnumTypeOfMIPMAP _typeOfMIPMAP;

    public:
        BaseTexture() = default;
        virtual ~BaseTexture() = default;

        void CreateTexture(std::string pathToTexture);
        void DeleteTexture();

        virtual bool TransferToGPU(
            bool genTextureAuto,
            bool unbindTextureAuto,
            EnumTypeOfTexture typeOfTexture) = 0;

        void SetTypeOfWrapping(EnumTypeOfWrapping xType, EnumTypeOfWrapping yType);
        void SetTypeOfTextureFiltering(EnumTypeOfTextureFiltering minType, EnumTypeOfTextureFiltering magType);
        void SetTypeOfMIPMAP(EnumTypeOfMIPMAP minType, EnumTypeOfMIPMAP magType);

        [[nodiscard]] unsigned int GetTextureId() const;
        [[nodiscard]] unsigned int GetTextureLocation() const;

        [[nodiscard]] unsigned int GetWidth() const;
        [[nodiscard]] unsigned int GetHeight() const;

        virtual bool BindTexture(unsigned int index, unsigned int programId, std::string samplerName) = 0;
    };
}


#include "BaseTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <filesystem>

#include <string>
#include <algorithm>
#include <GLEW/glew.h>

namespace Render::AnomalyEngine::Textures {
    void BaseTexture::CreateTexture(std::string pathToTexture) {
        int width, height, channelsCount;

#ifdef WINDOWS
        std::replace(pathToTexture.begin(), pathToTexture.end(), '/', '\\');
#else
        std::replace(pathToTexture.begin(), pathToTexture.end(), '\\', '/');
#endif

        stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load((std::filesystem::current_path().string() + pathToTexture).c_str(),
                                        &width, &height, &channelsCount, 0);

        if (data == nullptr) {
            std::cout << "Error: could not create texture. Check path: " << std::filesystem::current_path().string() + pathToTexture << std::endl;
            return;
        }

        _textureData = std::unique_ptr<unsigned char>(data);

        _width = width;
        _height = height;
        _channelsCount = channelsCount;
        std::cout << "Info: Texture was created from: " << std::filesystem::current_path().string() + pathToTexture << std::endl;
    }

    void BaseTexture::DeleteTextureFromRAM() {
        _textureData.reset();

        std::cout << "Info: Texture was deleted from RAM" << std::endl;
    }
    void BaseTexture::DeleteTextureFromVRAM() {
        if (_textureID == 0)
            return;

        glDeleteTextures(1, &_textureID);

        _width = 0;
        _height = 0;
        _channelsCount = 0;
        _textureID = 0;

        std::cout << "Info: Texture was deleted from VRAM" << std::endl;
    }

    unsigned int BaseTexture::GetTextureId() const
    {
        return _textureID;
    }

    unsigned int BaseTexture::GetTextureLocation() const
    {
        return textureLocation;
    }

    unsigned int BaseTexture::GetWidth() const
    {
        return _width;
    }

    unsigned int BaseTexture::GetHeight() const
    {
        return _height;
    }
}


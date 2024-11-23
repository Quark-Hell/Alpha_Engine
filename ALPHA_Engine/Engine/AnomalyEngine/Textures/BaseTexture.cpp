#include "BaseTexture.h"

#include "Core/Logger/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>

#include <string>
#include <algorithm>
#include <GLEW/glew.h>

namespace AnomalyEngine {
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
            Core::Logger::Logger::LogError("Could not create texture. Check path: ", std::filesystem::current_path().string() + pathToTexture);
            return;
        }

        _textureData = std::unique_ptr<unsigned char>(data);

        _width = width;
        _height = height;
        _channelsCount = channelsCount;
        Core::Logger::Logger::LogInfo("Texture created successfully");
    }

    void BaseTexture::DeleteTextureFromRAM() {
        _textureData.reset();
        Core::Logger::Logger::LogInfo("Texture was deleted from RAM");
    }
    void BaseTexture::DeleteTextureFromVRAM() {
        if (_textureID == 0)
            return;

        glDeleteTextures(1, &_textureID);
        _textureID = 0;

        Core::Logger::Logger::LogInfo("Texture was deleted from VRAM");
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


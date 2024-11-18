#include "OpenGLTexture.h"

#include <GLEW/glew.h>

#include "Logger/Logger.h"

namespace Render::WindowsManager::AnomalyEngine {

    OpenGLTexture::OpenGLTexture() {

    }
    OpenGLTexture::~OpenGLTexture() {

    }


    bool OpenGLTexture::TransferToGPU(const bool genTextureAuto, const EnumTypeOfTexture typeOfTexture) {
        if (_textureData == nullptr) {
            Logger::Logger::LogError("Texture has no data: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        int textureType;
        switch (typeOfTexture) {
            case Texture2D:
                textureType = GL_TEXTURE_2D;
                break;
            case TEXTURE_CUBE_MAP_POSITIVE_X:
                textureType = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
                break;
            case TEXTURE_CUBE_MAP_NEGATIVE_X:
                textureType = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
                break;
            case TEXTURE_CUBE_MAP_POSITIVE_Y:
                textureType = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
                break;
            case TEXTURE_CUBE_MAP_NEGATIVE_Y:
                textureType = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
                break;
            case TEXTURE_CUBE_MAP_POSITIVE_Z:
                textureType = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
                break;
            case TEXTURE_CUBE_MAP_NEGATIVE_Z:
                textureType = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
                break;
            default:
                Logger::Logger::LogError("Not allowed type of texture: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
                return false;
                break;
        }

        if (_textureID != 0) {
            glDeleteTextures(1, &_textureID);
            _textureID = 0;
            Logger::Logger::LogInfo("Old texture was deleted from VRAM");
        }

        if (genTextureAuto) {
            glGenTextures(1, &_textureID);
            glBindTexture(textureType, _textureID);
            Logger::Logger::LogInfo("Texture was binded");
        }

        if (BaseTexture::_width == 0 || BaseTexture::_height == 0 || BaseTexture::_channelsCount == 0) {
            Logger::Logger::LogError("width, height or channels count of texture equal is zero: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        int glInternalFormat = 0;
        if (BaseTexture::_channelsCount == 3) {
            glInternalFormat = GL_RGB;
        }
        else {
            glInternalFormat = GL_RGBA;
        }

        glTexImage2D(textureType,
             0,
             glInternalFormat,
             _width,
             _height,
             0,
             glInternalFormat,
             GL_UNSIGNED_BYTE,
             _textureData.get());

        Logger::Logger::LogInfo("Created texture with ", _channelsCount, " channels count");

        if (genTextureAuto) {
            glBindTexture(textureType, 0);
            Logger::Logger::LogInfo("Texture was unbinded");
            DeleteTextureFromRAM();
        }

        return true;
    }


    bool OpenGLTexture::BindTexture(const unsigned int index, const unsigned int programId, const std::string samplerName) {
        if (BaseTexture::_textureID != 0) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, BaseTexture::_textureID);

            BaseTexture::textureLocation = glGetUniformLocation(programId, samplerName.c_str());
            glUniform1i(BaseTexture::textureLocation, index);

            //std::cout << "Texture was be binded" << std::endl;
            return true;
        }

        Logger::Logger::LogError("Texture data does not exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        return false;
    }
}
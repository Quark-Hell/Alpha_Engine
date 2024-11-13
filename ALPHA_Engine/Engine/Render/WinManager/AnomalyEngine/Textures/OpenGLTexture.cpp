#include "OpenGLTexture.h"

#include <GLEW/glew.h>
#include <iostream>

namespace Render::AnomalyEngine::Textures {

    OpenGLTexture::OpenGLTexture() {

    }
    OpenGLTexture::~OpenGLTexture() {

    }


    bool OpenGLTexture::TransferToGPU(const bool genTextureAuto, const EnumTypeOfTexture typeOfTexture) {
        if (_textureData == nullptr) {
            std::cout << "Error: texture has no data" << std::endl;
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
                std::cout << "Error: Not allowed type of texture" << std::endl;
                return false;
                break;
        }

        if (_textureID != 0) {
            glDeleteTextures(1, &_textureID);
            _textureID = 0;
            std::cout << "Info: Old texture was deleted from VRAM" << std::endl;
        }

        if (genTextureAuto) {
            glGenTextures(1, &_textureID);
            glBindTexture(textureType, _textureID);
            std::cout << "Info: Texture was binded" << std::endl;
        }

        if (BaseTexture::_width == 0 || BaseTexture::_height == 0 || BaseTexture::_channelsCount == 0) {
            std::cout << "Error: width, height or channels count of texture equal is zero" << std::endl;
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

        std::cout << "Info: Created texture with " << _channelsCount << " channels count" << std::endl;

        if (genTextureAuto) {
            glBindTexture(textureType, 0);
            std::cout << "Info: Texture was unbinded" << std::endl;
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

            std::cout << "Info: Texture was be binded" << std::endl;
            return true;
        }

        std::cout << "Error: Texture data does not exist" << std::endl;
        return false;
    }
}
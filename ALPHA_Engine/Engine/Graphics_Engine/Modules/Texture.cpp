#include "Texture.h"
#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {

}

Texture::~Texture() {

}

void Texture::CreateTexture(std::string pathToTexture) {
	int width, height, channelsCount;

	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load((std::filesystem::current_path().string() + pathToTexture.c_str()).c_str(), &width, &height, &channelsCount, 0);
	Texture::_textureData = std::unique_ptr<unsigned char>(data);

	Texture::_width = width;
	Texture::_height = height;
	Texture::_channelsCount = channelsCount;
}

void Texture::DeleteTexture()
{
	Texture::_textureData.reset();
}

bool Texture::TransferToGPU(bool genTextureAuto, bool unbindTextureAuto, EnumTypeOfTexture typeOfTexture)
{
    if (Texture::_textureData.get() == nullptr)
        return false;

    int textureType;
    switch (typeOfTexture)
    {
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
        return false;
        break;
    }

    if (genTextureAuto) {
        glGenTextures(1, &textureId);
        glBindTexture(textureType, textureId);
    }


    if (Texture::_textureData == nullptr) {
        std::cout << "Error load texture: undefined path to texture\n";
        return false;
    }

    if (Texture::_width == 0 || Texture::_height == 0 || Texture::_channelsCount == 0) {
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    if (Texture::_channelsCount == 3) {
        glTexImage2D(textureType,
            0,
            GL_RGB,
            Texture::_width,
            Texture::_height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            Texture::_textureData.get());
    }
    else if (Texture::_channelsCount == 4) {
        glTexImage2D(textureType,
            0,
            GL_RGBA,
            Texture::_width,
            Texture::_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            Texture::_textureData.get());
    }

    Texture::DeleteTexture();

    if (unbindTextureAuto) {
        glBindTexture(textureType, 0);
    }

    return true;
}

unsigned int Texture::GetTextureId()
{
	return Texture::textureId;
}

unsigned int Texture::GetTextureLocation()
{
	return Texture::textureLocation;
}

unsigned int Texture::GetWidth()
{
    return Texture::_width;
}

unsigned int Texture::GetHeight()
{
    return Texture::_height;
}

bool Texture::BindTexture(unsigned int index, unsigned int programId, std::string samplerName)
{
	if (Texture::textureId != 0) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, Texture::textureId);

		Texture::textureLocation = glGetUniformLocation(programId, samplerName.c_str());
		glUniform1i(Texture::textureLocation, index);

		return true;
	}

	return false;
}

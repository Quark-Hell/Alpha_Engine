#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {

}

Texture::~Texture() {

}

void Texture::CreateTexture(std::string pathToTexture) {
	int width, height, channelsCount;

	stbi_set_flip_vertically_on_load(true);
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

bool Texture::TransferToGPU()
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

    if (Texture::_textureData == nullptr) {
        std::cout << "Error load texture: undefined path to texture\n";
        return false;
    }

    if (Texture::_width == 0 || Texture::_height == 0 || Texture::_channelsCount == 0) {
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    if (Texture::_channelsCount == 3) {
        glTexImage2D(GL_TEXTURE_2D,
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
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            Texture::_width,
            Texture::_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            Texture::_textureData.get());
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    Texture::DeleteTexture();

    glBindTexture(GL_TEXTURE_2D, 0);
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

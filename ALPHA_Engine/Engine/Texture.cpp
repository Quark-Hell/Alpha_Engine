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
	Texture::_texture = std::unique_ptr<unsigned char>(data);

	Texture::_width = width;
	Texture::_height = height;
	Texture::_channelsCount = channelsCount;
}

void Texture::DeleteTexture()
{
	stbi_image_free(Texture::_texture.get());
}

#pragma once
#include "Basical_Type.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define GLEW_STATIC
#include <GL/glew.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <GL/gl.h>
#include <GL/glu.h>

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

enum EnumTypeOfTexture {
	Texture2D = 0,
	TEXTURE_CUBE_MAP_POSITIVE_X = 1,
	TEXTURE_CUBE_MAP_NEGATIVE_X = 2,
	TEXTURE_CUBE_MAP_POSITIVE_Y = 3,
	TEXTURE_CUBE_MAP_NEGATIVE_Y = 4,
	TEXTURE_CUBE_MAP_POSITIVE_Z = 5,
	TEXTURE_CUBE_MAP_NEGATIVE_Z = 6
};

class Texture {
	//https://dtf.ru/gamedev/244935-iz-chego-sostoit-grafika#first

	friend class Material;
	friend class Render;
	friend class Mesh;

private:
	std::string _texturePath;
public:
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
	Texture();
	~Texture();

	void CreateTexture(std::string pathToTexture);
	void DeleteTexture();

	bool TransferToGPU(bool genTextureAuto = true, bool unbindTextureAuto = true, EnumTypeOfTexture typeOfTexture = EnumTypeOfTexture::Texture2D);

	void SetTypeOfWrapping(EnumTypeOfWrapping xType, EnumTypeOfWrapping yType);
	void SetTypeOfTextureFiltering(EnumTypeOfTextureFiltering minType, EnumTypeOfTextureFiltering magType);
	void SetTypeOfMIPMAP(EnumTypeOfMIPMAP minType, EnumTypeOfMIPMAP magType);

	unsigned int GetTextureId();
	unsigned int GetTextureLocation();

	unsigned int GetWidth();
	unsigned int GetHeight();

	bool BindTexture(unsigned int index, unsigned int programId, std::string samplerName);
};

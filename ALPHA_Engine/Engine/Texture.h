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
#include <gl/gl.h>
#include <gl/glu.h>

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

class Texture {
	//https://dtf.ru/gamedev/244935-iz-chego-sostoit-grafika#first

	friend class Material;
	friend class Render;
	friend class Mesh;

private:
	std::string _texturePath;

	std::unique_ptr<unsigned char> _texture = std::unique_ptr<unsigned char>();

	unsigned int _width;
	unsigned int _height;
	unsigned int _channelsCount;

	GLuint textureId;

	//Other representation(DirectX, Vulkan...)

	EnumTypeOfWrapping _typeOfWrapping;
	EnumTypeOfTextureFiltering _typeOfTextureFiltering;
	EnumTypeOfMIPMAP _typeOfMIPMAP;

public:
	Texture();
	~Texture();

	void CreateTexture(std::string pathToTexture);
	void DeleteTexture();

	void SetTypeOfWrapping(EnumTypeOfWrapping xType, EnumTypeOfWrapping yType);
	void SetTypeOfTextureFiltering(EnumTypeOfTextureFiltering minType, EnumTypeOfTextureFiltering magType);
	void SetTypeOfMIPMAP(EnumTypeOfMIPMAP minType, EnumTypeOfMIPMAP magType);
};

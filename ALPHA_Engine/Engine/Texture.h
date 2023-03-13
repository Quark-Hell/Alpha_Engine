#pragma once
#include "Basical_Type.h"

//SFML
//#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>
//#include <SFML/Graphics.hpp>

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

private:
	std::string _textureLink;
	std::vector <Vector3> _textureCoords;

	//sf::Texture _sfTexture;
	//Other representation(DirectX, Vulkan...)

	EnumTypeOfWrapping _typeOfWrapping;
	EnumTypeOfTextureFiltering _typeOfTextureFiltering;
	EnumTypeOfMIPMAP _typeOfMIPMAP;

public:
	void CreateTexture(unsigned int width, unsigned int height);

	void SetTypeOfWrapping(EnumTypeOfWrapping xType, EnumTypeOfWrapping yType);
	void SetTypeOfTextureFiltering(EnumTypeOfTextureFiltering minType, EnumTypeOfTextureFiltering magType);
	void SetTypeOfMIPMAP(EnumTypeOfMIPMAP minType, EnumTypeOfMIPMAP magType);
};

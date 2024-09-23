#pragma once
#include "BaseConfig.h"

class GLFWwindow;

class Screen
{
	friend class Graphics_Engine;

private:
	unsigned int _wight = 0;
	unsigned int _height = 0;
	unsigned int _bitsPerPixel = 0;
	std::string _name;

	GLFWwindow* _window = nullptr;

public:
	~Screen();
	GLFWwindow* GetWindow();

private:
	Screen();
	void CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name);
};


#pragma once
#include "BaseConfig.h"

class GLFWwindow;

namespace GraphicsEngine {
	class Screen
	{
		friend class RenderCore;

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
}

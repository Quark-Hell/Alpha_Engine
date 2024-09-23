#pragma once
#include "BaseConfig.h"

class Graphics_Engine;

class Host
{
	friend class World;

private:
	std::unique_ptr<Graphics_Engine> _graphics_engine;

private:
	static std::unique_ptr<Host> MakeHost();
	Host();

public:
	~Host();

	void StartRender();

	void Graphics();
	void Physics();
};


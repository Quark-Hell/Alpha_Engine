#pragma once
#include "ShaderProgram.h"

class CubeMapShader : public ShaderProgram {
private:
	Texture _rightSide;
	Texture _leftSide;
	Texture _topSide;
	Texture _bottomSide;
	Texture _frontSide;
	Texture _backSide;

	unsigned int _textureId;

public:
	CubeMapShader(Material* parentMat);
	~CubeMapShader();

	bool LoadTexture(
		std::string rightTexture,
		std::string leftTexture,
		std::string topTexture,
		std::string bottomTexture,
		std::string frontTexture,
		std::string backTexture);

	void ApplyShadersSettings(std::shared_ptr<Camera> camera) override;
};
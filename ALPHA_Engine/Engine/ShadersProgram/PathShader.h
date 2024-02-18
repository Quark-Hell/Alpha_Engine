#pragma once
#include "ShaderProgram.h"

class PathShader : public ShaderProgram {
private:
	std::vector<Vector3> points;
	const int maxPoints = 500;
	int pointsCount = -1;
	
public:
	Vector3 LineColor = Vector3(0.851, 0.851, 0.851);
	float LineWidth = 2.0f;

public:
	PathShader(Material* parentMat);
	~PathShader();

	void ApplyShadersSettings(std::shared_ptr<Camera> camera) override;
	void AddPoint(Vector3 point);
};
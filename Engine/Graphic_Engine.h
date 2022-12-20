#pragma once
#include <iostream>
#include "Basical_Type.h"
#include "Graphic_Engine.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <gl/gl.h>
#include <gl/glu.h>

class Camera {
private:
	Vector3 Position;
	Vector3 Rotation;

private:
	float Fov;
	float Aspect;
	float ZNear;
	float ZFar;

public:
	void SetCameraInfo(Vector3 Position, Vector3 Rotation, float Fov, float Aspect, float ZNear, float ZFar);
	void GetCameraInfo(Vector3* Position, Vector3* Rotation, float* Fov, float* Aspect, float* ZNear, float* ZFar);
};

class Render {

private:
	void  PrepareToRender(Camera* camera);

private:
	void Draw(sf::RenderWindow& App);

public:
	void RenderMesh();

public:
	void RenderLoop();
};

class Output {

};
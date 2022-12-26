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

struct Colors {
	const Vector3 green { 0.0f, 1.0f, 0.0f }; 
	const Vector3 orange {	1.0f, 0.5f, 0.0f}; 
	const Vector3 red {	1.0f, 0.0f, 0.0f};    
	const Vector3 yellow{	1.0f, 1.0f, 0.0f};  
	const Vector3 blue{	0.0f, 0.0f, 1.0f};    
	const Vector3 violet{ 1.0f, 0.0f, 1.0f };   
};

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

public:
	void Assembler(Object* obj, Mesh* mesh);

public:
	void ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale);
};

class Output {

};
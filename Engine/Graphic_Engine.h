#pragma once

#include <iostream>
#include "Basical_Type.h"
#include "IO.h"

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

class Screen {
private:
	unsigned int _wight;
	unsigned int _height;
	unsigned int _bitsPerPixel;
	std::string _name;
	sf::ContextSettings _screen_Settings;

	sf::RenderWindow* _screen;

	friend class Render;

private:
	void CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name, sf::ContextSettings Screen_Settings);
};

class Render {

private:
	Screen _screenClass;

private:
	void  PrepareToRender(Camera* camera);

	void ClearFrameBuffer();

public:
	void RenderMesh();

	void RenderLoop();

	void Assembler(Object* obj, Mesh* mesh);

	void ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale);
};

class Output {

};
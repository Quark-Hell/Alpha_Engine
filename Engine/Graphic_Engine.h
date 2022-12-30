#pragma once

#include <iostream>
#include "Basical_Type.h"

//SFML
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
	Vector3 Position = Vector3{0,0,0};
	Vector3 Rotation = Vector3{0,0,0};

private:
	float Fov = 90;
	float Aspect = 1;
	float ZNear = 1;
	float ZFar = 300;

public:
	void SetCameraInfo(Vector3 Position, Vector3 Rotation);
	void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
	void SetCameraInfo(Vector3 Position, Vector3 Rotation, float Fov, float Aspect, float ZNear, float ZFar);
	void GetCameraInfo(Vector3* Position, Vector3* Rotation, float* Fov, float* Aspect, float* ZNear, float* ZFar);

	Vector3 GetPosition();
	Vector3 GetRotation();
	float GetFov();
	float GetAspect();
	float GetZNear();
	float GetZFar();
};

class Screen {
private:
	unsigned int _wight;
	unsigned int _height;
	unsigned int _bitsPerPixel;
	std::string _name;
	sf::ContextSettings _screen_Settings;

	sf::RenderWindow* _screen;

private:
	friend class Render;
	friend class InputSystem;

private:
	void CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name, sf::ContextSettings Screen_Settings);
};

class Render {

private:
	Screen _screenClass;

private:
	void  PrepareToRender();
	void ClearFrameBuffer();

public:
	 void StartRender(Camera* camera);
	 void RenderLoop(Camera* camera);
	Screen* GetScreenClass();

private:
	void ApplyCameraTransform(Camera* camera);
	void SceneAssembler();
	void RenderMesh(Mesh* mesh);
	void ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale);
};

class Output {

};
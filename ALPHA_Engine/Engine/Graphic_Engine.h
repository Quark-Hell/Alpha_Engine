#pragma once

#include <iostream>
#include "Basical_Type.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameModels.h"

//SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

//OpenGL
/*
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
*/
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

public:
	sf::RenderWindow* GetScreen();
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


public:
	void DebugRender(std::vector<Vector3> *Vertex, std::vector<Vector3>* Normals, Camera* camera);
	void RenderVertArray(std::vector<Vector3>* Vertex, std::vector<Vector3>* Normals);
};

class Output {

};
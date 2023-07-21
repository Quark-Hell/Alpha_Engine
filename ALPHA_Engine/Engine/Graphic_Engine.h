#pragma once

#include "Basical_Type.h"

class Camera;
class Mesh;

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

	GLFWwindow* _window;

private:
	friend class Render;
	friend class InputSystem;

private:
	void CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name);

public:
	GLFWwindow* GetWindow();
};

class Render {

private:
	Screen _screenClass;

private:
	void PrepareToRender();
	void ClearFrameBuffer();

public:
	void StartRender(Camera* camera);
	void RenderLoop(Camera* camera);
	Screen* GetScreenClass();

private:
	void SceneAssembler();

	void RenderMesh(Mesh& mesh);
	void RenderMeshCollider(Geometry& collider);
	//void RenderCollider(ColliderPresets& collider);

	void ApplyCameraTransform(Camera* camera);
	void ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale);
};
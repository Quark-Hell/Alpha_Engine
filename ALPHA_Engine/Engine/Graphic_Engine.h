#pragma once

#include "Basical_Type.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <gl/gl.h>
#include <gl/glu.h>

class Camera;
class Geometry;
class Collider;
class BoxCollider;
class Mesh;
class Vector3;
class RigidBody;
class Material;
class AABB;
class Node;
class MeshCollider;

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
	void StartRender(std::shared_ptr<Camera> camera);
	void RenderLoop(std::shared_ptr<Camera>  camera);
	Screen* GetScreenClass();

	bool CompileShaders();

private:
	void SceneAssembler(std::shared_ptr<Camera> camera);

	void SetMeshRenderOptions();
	void SetDebugRenderOptions();
	void SetCubeMapRenderOptions();


	void RenderMesh(Mesh& mesh, std::shared_ptr<Camera>  camera);
	void RenderAABB(std::vector<float>& vertex, std::vector<unsigned int>& indices);
	void RenderWorldAABB(Node& rootNode);
	void RenderCubeMap(Mesh& mesh, std::shared_ptr<Camera>  camera);

	void RenderRigidBodyInfo(RigidBody& rb);

	void ApplyCameraTransform(std::shared_ptr<Camera>  camera);
};
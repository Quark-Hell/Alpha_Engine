
#include "Graphics_Engine.h"
#include "BaseConfig.h"

#include "Core/Math/Vectors.h"

#include "Graphics_Engine/Modules/Screen.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <Gl/gl.h>
#include <Gl/glu.h>

#include "gtc/type_ptr.hpp"

enum RenderModes : unsigned short {
    Points = 0,
    LineStip = 1,
    LineLoop = 2,
    Lines = 3,
    LineStripAdjacency = 4,
    LinesAdjacency = 5,
    TriangleStrip = 6,
    TriangleFan = 7,
    Triangles = 8,
    TriangleStripAdjacency = 9,
    TrianglesAdjacency = 10,
    Patches = 11,
};

std::unique_ptr<Graphics_Engine> Graphics_Engine::MakeGraphics_Engine() {
    return std::unique_ptr<Graphics_Engine>(new Graphics_Engine());
}

Graphics_Engine::Graphics_Engine() {

}

Graphics_Engine::~Graphics_Engine() {

}

Screen* Graphics_Engine::GetScreenClass() {
    return &(Graphics_Engine::_screenClass);
}

void Graphics_Engine::PrepareToRender() {
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics_Engine::ClearFrameBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graphics_Engine::StartRender() {
    _screenClass.CreateScreen(1280, 720, 32, "GLFW OpenGL");

    int width, height;
    glfwGetFramebufferSize(_screenClass._window, &width, &height);
    glViewport(0, 0, width, height);

    Graphics_Engine::PrepareToRender();
    //Render::ApplyCameraTransform(camera);

    //camera->SetCameraInfo(60, 16.0 / 9.0, 0.1, 300);
}

void Graphics_Engine::RenderLoop() {
    if (!glfwWindowShouldClose(_screenClass._window))
    {
        glfwPollEvents();//make render more slower

        Graphics_Engine::ClearFrameBuffer();

        Graphics_Engine::PrepareToRender();
        //Render::ApplyCameraTransform(camera);

        //Graphics_Engine::SceneAssembler(camera);

        glFinish();
        glfwSwapBuffers(_screenClass._window);
    }
    else
    {
        exit(0);
    }
}
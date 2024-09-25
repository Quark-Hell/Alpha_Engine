#include "Graphics_Engine/Modules/Screen.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <Gl/gl.h>
#include <Gl/glu.h>

GraphicsEngine::Screen::Screen() {

}

GraphicsEngine::Screen::~Screen() {

}

void GraphicsEngine::Screen::CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name) {
    _wight = Wight;
    _height = Height;
    _bitsPerPixel = BitsPerPixel;
    _name = Name;

    if (!glfwInit()) {
        glfwTerminate();
    }

    Screen::_window = glfwCreateWindow(Wight, Height, Name.c_str(), nullptr, nullptr);
    if (Screen::_window == nullptr)
    {
        //TODO: Add exception
        //std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    int width, height;
    glfwGetFramebufferSize(Screen::_window, &width, &height);
    glViewport(0, 0, width, height);

    glfwMakeContextCurrent(Screen::_window);
    glfwSwapInterval(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    //GLEW Init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        //TODO: Add exception
        //std::cout << "Failed to initialize GLEW" << std::endl;
        //
        glfwTerminate();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    ////Todo:
    ////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) if MacOs
}
GLFWwindow* GraphicsEngine::Screen::GetWindow() {
    return Screen::_window;
}
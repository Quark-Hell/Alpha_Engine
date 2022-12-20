#include <iostream>
#include "Graphic_Engine.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <gl/gl.h>
#include <gl/glu.h>

#include "GameModels.h"

inline void Camera::SetCameraInfo(Vector3 Position, Vector3 Rotation, float Fov, float Aspect, float ZNear, float ZFar) {
    Camera::Fov = Fov;
    Camera::Aspect = Aspect;
    Camera::ZNear = ZNear;
    Camera::ZFar = ZFar;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Fov, Aspect, ZNear, ZFar);
    glTranslatef(Position.X, Position.Y, Position.Z);
}

inline void Camera::GetCameraInfo(Vector3* Position, Vector3* Rotation, float* Fov, float* Aspect, float* ZNear, float* ZFar) {
    *Position = Camera::Position;
    *Rotation = Camera::Rotation;
    *Fov = Camera::Fov;
    *Aspect = Camera::Aspect;
    *ZNear = Camera::ZNear;
    *ZFar = Camera::ZFar;
}

inline void Render::PrepareToRender(Camera *camera) {
    Vector3 Position;
    Vector3 Rotation;

    float Fov;
    float Aspect;
    float ZNear;
    float ZFar;

    camera->GetCameraInfo(&Position, &Rotation, &Fov, &Aspect, &ZNear, &ZFar);

    glClearColor(0.3f, 0.3f, 0.3f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE); // enable culling face
    glCullFace(GL_BACK); // cull faces from back
    glFrontFace(GL_CCW); // vertex order (counter clock wise)

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Fov, Aspect, ZNear, ZFar);

    glTranslatef(Position.X, Position.Y, Position.Z);

    glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(Rotation.Z, 0.f, 0.f, 1.f);
}

inline void Render::Draw(sf::RenderWindow& App) {
    //Prepare for drawing
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    App.display();
}

//arg: sf::RenderWindow App
inline void Render::RenderLoop() {
    //GLfloat CamX = 0;

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    Camera camera;

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL");
    Render::PrepareToRender(&camera);

    glEnable(GL_LIGHTING);

    camera.SetCameraInfo(Vector3{ 1.5f,0,0 }, Vector3{0,0,0},90,1,1,300);

    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float angle = Clock.getElapsedTime().asSeconds() * 5;

        // Apply some transformations for the cube
        Vector3 Postion{ 1,0,-5 };
        Vector3 Rotation(0, 30 * angle, 40);
        Vector3 Scale{ 1,1,1 };
        Vector3 Color{ 0,0,1 };

        Primitive::Cube(Postion, Rotation, Scale, Color);

        // Apply some transformations for the cube
        Vector3 Postion1{ -4,0,-5 };
        Vector3 Rotation1(0, 30 * -angle, 40);
        Vector3 Scale1{ 1,1,1 };
        Vector3 Color1{ 0,1,1 };

        Primitive::Cube(Postion1, Rotation1, Scale1, Color1);

        App.display();
    }
}

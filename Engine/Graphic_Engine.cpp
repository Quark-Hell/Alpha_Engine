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

    //Light
    GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

    GLfloat LightAmbient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);

    GLfloat LightDiffuse[] = { 0.75f, 0.75f, 0.75f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);

    GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

    GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_CULL_FACE); // enable culling face
    glCullFace(GL_BACK); // cull faces from back
    glFrontFace(GL_CCW); // vertex order (counter clock wise)

    glEnable(GL_COLOR_MATERIAL);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LEQUAL);

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

inline void Render::ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(Position.X, Position.Y, Position.Z);

    glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(Rotation.Z, 0.f, 0.f, 1.f);

    glScalef(Scale.X, Scale.Y, Scale.Z);
}

inline void Render::Assembler(Object *obj, Mesh *mesh) {
    Render::ApplyTransformation(obj->GetPosition(), obj->GetRotation(), obj->GetScale());

    glBegin(GL_TRIANGLES);//draw some squares
    glColor3f(1,0,0);

    for (size_t i = 0; i < mesh->Points.size(); i++)
    {
        glNormal3f(mesh->Normals[i].X, mesh->Normals[i].Y, mesh->Normals[i].Z);
        glVertex3f( mesh->Points[i].X, mesh->Points[i].Y, mesh->Points[i].Z);
    }

    glEnd();
}       

//arg: sf::RenderWindow App
inline void Render::RenderLoop() {

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    Camera camera;

    sf::ContextSettings window_settings;
    window_settings.depthBits = 24;
    window_settings.stencilBits = 8;
    window_settings.antialiasingLevel = 2;

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Resize | sf::Style::Close , window_settings);
    Render::PrepareToRender(&camera);

    camera.SetCameraInfo(Vector3{ 0,0, 0 }, Vector3{ 0,0,0 }, 60, 1, 1, 300);

    App.setVerticalSyncEnabled(true);

    std::string link = "C:/Users/genna/source/repos/3DRotate/Models/text.fbx";
    Object obj;
    Mesh mesh;
    mesh.CreateMesh(link);
    obj.AddModule(mesh);

    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        if (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float angle = Clock.getElapsedTime().asSeconds() * 50;

        /*
        // Apply some transformations for the cube
        Vector3 Postion{ 1,0,-5 };
        Vector3 Rotation(0, 30 * angle, 40);
        Vector3 Scale{ 1,1,1 };
        Vector3 Color{ 0,0,1 };

        Primitive::Cube(Postion, Rotation, Scale, Color);

         */

        obj.SetPosition(0, 0, -3);
        obj.SetRotation(0, obj.GetRotation().X + angle, 0);

        Render::Assembler(&obj, &mesh);

        App.display();
    }
}

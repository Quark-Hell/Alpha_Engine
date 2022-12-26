#include "GameModels.h"

//SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <gl/gl.h>
#include <gl/glu.h>

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//TODO: Function normilize color

void Primitive::Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    //Render::ApplyTransformation(Position, Rotation, Scale);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(Position.X, Position.Y, Position.Z);

    glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(Rotation.Z, 0.f, 0.f, 1.f);

    glScalef(Scale.X, Scale.Y, Scale.Z);

    //Draw a cube
    glBegin(GL_QUADS);//draw some squares

    glColor3f(Color.X, Color.Y, Color.Z);

    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Quad (Top)
    glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Quad (Top)


    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(1.0f, -1.0f, 1.0f);  // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Bottom)
    glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Bottom)


    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Front)
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Front)


    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(1.0f, -1.0f, -1.0f);  // Top Right Of The Quad (Back)
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Bottom Left Of The Quad (Back)
    glVertex3f(1.0f, 1.0f, -1.0f);  // Bottom Right Of The Quad (Back)


    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Left)
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Left)


    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Right)
    glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Right)
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Right)
    glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Right)

    glEnd();
}

void Primitive::Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::UVSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::IcoSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}

void Primitive::Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {

}
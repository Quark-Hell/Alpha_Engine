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

//TODO: Function normilize color

/* TODO: Form colors enum
glColor3f(0.0f, 1.0f, 0.0f);  // Color Green
glColor3f(1.0f, 0.5f, 0.0f);  // Color Orange
glColor3f(1.0f, 0.0f, 0.0f);    // Color Red
glColor3f(1.0f, 1.0f, 0.0f);    // Color Yellow
glColor3f(0.0f, 0.0f, 1.0f);    // Color Blue
glColor3f(1.0f, 0.0f, 1.0f);    // Color Violet
*/

void Primitive::ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(Position.X, Position.Y, Position.Z);

    glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(Rotation.Z, 0.f, 0.f, 1.f);

    glScalef(Scale.X, Scale.Y, Scale.Z);
}

void Primitive::Plane(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::Cube(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);

    //Draw a cube
    glBegin(GL_QUADS);//draw some squares

    glColor3f(Color.X, Color.Y, Color.Z);

    glNormal3f(0.f , 1.f, 0.f);
    glVertex3f(1.0f , 1.0f, -1.0f);  // Top Right Of The Quad (Top)
    glNormal3f(0.f , 1.f, 0.f);
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Top)
    glNormal3f(0.f , 1.f, 0.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Quad (Top)
    glNormal3f(0.f , 1.f, 0.f);
    glVertex3f(1.0f , 1.0f, 1.0f);  // Bottom Right Of The Quad (Top)


    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(1.0f, -1.0f, 1.0f);  // Top Right Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Bottom)


    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f );
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Front)


    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(1.0f, -1.0f, -1.0f);  // Top Right Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Left Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Bottom Left Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(1.0f, 1.0f, -1.0f);  // Bottom Right Of The Quad (Back)


    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Left)


    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Right)

    glEnd();
}

void Primitive::Circle(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::UVSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::IcoSphere(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::Cylinder(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::Cone(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}

void Primitive::Torus(Vector3 Position, Vector3 Rotation, Vector3 Scale, Vector3 Color) {
    Primitive::ApplyTransformation(Position, Rotation, Scale);
}
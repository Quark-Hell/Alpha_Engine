#include "Graphic_Engine.h"

#include "World.h"
#include "Modules/Camera.h"
#include "Modules/Geometry.h"
#include "Modules/Mesh.h"
#include "Modules/SubModules/Material.h"

#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"

#include "Modules/Physics.h"

#include "Collision.h"

#include "AABB.h"
#include "BVH_Tree.h"

#include "GameModels.h"

#include "gtc/type_ptr.hpp"

#include "ShaderProgram.h"

void Screen::CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name) {
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


    
    glfwWindowHint(GLFW_SAMPLES,3);

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

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    
    ////Todo:
    ////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) if MacOs
}
GLFWwindow* Screen::GetWindow() {
    return Screen::_window;
}

Screen* Render::GetScreenClass() {
    return &(Render::_screenClass);
}

void Render::PrepareToRender() {
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
    
    //glEnable(GL_CULL_FACE); // enable culling face
    //glCullFace(GL_BACK); // cull faces from back
    //glFrontFace(GL_CCW); // vertex order (counter clock wise)
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_COLOR_MATERIAL);
    
    //// Enable Z-buffer read and write
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);
    //glClearDepth(1.f);
    //glDepthFunc(GL_LEQUAL);
    
    float ratio = 4.0f / 3.0f;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.0f, 500.f);
}

void Render::ApplyCameraTransform(std::shared_ptr<Camera> camera) {
    Vector3 Position = camera->GetParentObject()->GetPosition();
    Vector3 Rotation = camera->GetParentObject()->GetRotation();

    float Fov;
    float Aspect;
    float ZNear;
    float ZFar;

    camera->GetCameraInfo(&Fov, &Aspect, &ZNear, &ZFar);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Fov, Aspect, ZNear, ZFar);

    glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(Rotation.Z, 0.f, 0.f, 1.f);

    glTranslatef(Position.X, Position.Y, Position.Z);
}

void Render::ClearFrameBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render::ApplyTransformation(Vector3 Position, Vector3 Rotation, Vector3 Scale) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(Position.X, Position.Y, Position.Z);

    //glRotatef(Rotation.X, 1.f, 0.f, 0.f);
    //glRotatef(Rotation.Y, 0.f, 1.f, 0.f);
    //glRotatef(Rotation.Z, 0.f, 0.f, 1.f);

    //glScalef(Scale.X, Scale.Y, Scale.Z);
}

void Render::SetMeshRenderOptions() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}
void Render::SetDebugRenderOptions() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Render::RenderMesh(Mesh& mesh) {
    Render::SetMeshRenderOptions();
    glColor3f(0.8, 0.8, 0.8);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    Material* mat = (Material*)mesh.GetSubModuleByType(MaterialType).get();
    if (mat != nullptr) {
        //glClientActiveTexture(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mat->_diffuse.textureId);
    }
   

    //glIndexPointer(GL_UNSIGNED_INT,0, mesh._indices);
    glTexCoordPointer(2, GL_FLOAT,0, mat->_texCoords.get());
    glNormalPointer(GL_FLOAT, 0, mesh._normals);
    glVertexPointer(3, GL_FLOAT, 0, mesh._vertex);
    
    glDrawElements(GL_TRIANGLES, mesh._indicesCount, GL_UNSIGNED_INT, mesh._indices);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Render::RenderCollider(Collider& collider) {
    Render::SetDebugRenderOptions();
    glColor3f(0.2, 0.8, 0.2);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &collider._debugVertex[0]);
    glDrawElements(GL_TRIANGLES, collider._debugIndices.size(), GL_UNSIGNED_INT, &collider._debugIndices[0]);

    glColor3f(0.8, 0.2, 0.2);
    glPointSize(7);
    glDrawElements(GL_POINTS, collider._debugIndices.size(), GL_UNSIGNED_INT, &collider._debugIndices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
}
void Render::RenderRigidBodyInfo(RigidBody& rb) {
    std::vector<Vector3> contactPoint;
    if (!rb.GetContactPoints(contactPoint))
        return;

    Render::SetDebugRenderOptions();
    glDisable(GL_DEPTH_TEST);
    glColor3f(0.2, 0.2, 0.7);
    glPointSize(10);

    std::cout << contactPoint.size() << " Size\n";

    for (size_t i = 0; i < contactPoint.size(); i++) {
        Vector3 relativeContactPointPos = (rb.GetParentObject()->GetPosition() * -1) + contactPoint[i];

        glBegin(GL_POINTS);
        glVertex3f(relativeContactPointPos.X, relativeContactPointPos.Y, relativeContactPointPos.Z);
        glEnd();
    }

}
void Render::RenderAABB(std::vector<float>& vertex, std::vector<unsigned int>& indices) {
#ifdef _DEBUG
    Render::SetDebugRenderOptions();
    //glDisable(GL_DEPTH_TEST);
    glColor3f(0.8, 0.8, 0.8);
    
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertex[0]);
    glDrawElements(GL_LINE_LOOP, indices.size(), GL_UNSIGNED_INT, &indices[0]);
    
    glDisableClientState(GL_VERTEX_ARRAY);
#endif // _DEBUG
}
void Render::RenderWorldAABB(Node& rootNode) {
#ifdef _DEBUG
    Render::SetDebugRenderOptions();
    //glDisable(GL_DEPTH_TEST);
    glColor3f(0.5, 0, 0.5);

    glEnableClientState(GL_VERTEX_ARRAY);


    glVertexPointer(3, GL_FLOAT, 0, &rootNode.AABBvolume._AABBvertex[0]);
    glDrawElements(GL_LINE_LOOP, rootNode.AABBvolume._AABBindices.size(), GL_UNSIGNED_INT, &rootNode.AABBvolume._AABBindices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
#endif // _DEBUG
}

void Render::SceneAssembler() {
    for (size_t i = 0; i < World::ObjectsOnScene.size(); i++)
    {
        for (size_t j = 0; j < World::ObjectsOnScene[i]->GetCountOfModules(); j++)
        {
            ModulesList type = World::ObjectsOnScene[i]->GetModuleByIndex(j)->GetType();

            if (type == MeshType) {
                std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(World::ObjectsOnScene[i]->GetModuleByIndex(j));
                Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                RenderMesh(*mesh);
            }


#pragma region DebugRender
#ifdef _DEBUG
            if (World::DebugRenderEnabled == false)
                continue;

            std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(World::ObjectsOnScene[i]->GetModuleByIndex(j));

            if (collider != nullptr) {
                Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                RenderCollider(*collider);
                RenderAABB(collider->_AABBvertex, collider->_AABBindices);
            }

            std::shared_ptr<RigidBody> rb = std::dynamic_pointer_cast<RigidBody>(World::ObjectsOnScene[i]->GetModuleByIndex(j));

            if (rb != nullptr) {
                Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                RenderRigidBodyInfo(*rb);
            }
#endif
#pragma endregion
        }
    } 

#ifdef _DEBUG
    //TODO: BVH Tree does not work now
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(
    //    World::RootBVHnode.get()->AABBvolume.GetAABBPosition().X, 
    //    World::RootBVHnode.get()->AABBvolume.GetAABBPosition().Y, 
    //    World::RootBVHnode.get()->AABBvolume.GetAABBPosition().Z);
    //
    //Render::RenderWorldAABB(*World::RootBVHnode.get());
#endif
}       

void Render::StartRender(std::shared_ptr<Camera>  camera) {
    _screenClass.CreateScreen(1280, 720, 32, "GLFW OpenGL");

    int width, height;
    glfwGetFramebufferSize(_screenClass._window, &width, &height);
    glViewport(0, 0, width, height);

    Render::PrepareToRender();
    Render::ApplyCameraTransform(camera);

    camera->SetCameraInfo(60, 16.0 / 9.0, 0.1, 300);
}

GLfloat points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

ShaderProgram shader;

GLuint points_vbo;
GLuint colors_vbo;
GLuint vao;

bool Render::CompileShaders() {
    shader.CreateShader("\\Shaders\\BaseVertexShaders\\VertexShader.txt", ShadersType::VertexShader);
    shader.CreateShader("\\Shaders\\BaseFragmentShaders\\FragmentShader.txt", ShadersType::FragmentShader);

    shader.CompileShader();


    if (shader.GetCompiledStatus()) {
        shader.AttachShader();
        shader.DeleteShader();

        points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        return true;
    }
    else
    {
        shader.DeleteShader();
    }
}

void Render::SetMatrix4(const char* name, const glm::mat4& matrix) const
{
    //glUniformMatrix4fv(glGetUniformLocation(shader_program, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Render::RenderLoop(std::shared_ptr<Camera>  camera) {
    if (!glfwWindowShouldClose(_screenClass._window))
    {
        glfwPollEvents();

        Render::ClearFrameBuffer();

        Render::PrepareToRender();
        //Render::ApplyCameraTransform(camera);

        //Render::SceneAssembler();
        if (shader.GetCompiledStatus() == true) {
            glUseProgram(shader.GetProgramId().value());
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }


        glfwSwapBuffers(_screenClass._window);
    }
    else
    {
        exit(0);
    }
}
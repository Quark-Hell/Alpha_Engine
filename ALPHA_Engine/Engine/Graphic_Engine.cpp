#include "Graphic_Engine.h"

#include "World.h"
#include "Modules/Camera.h"
#include "Modules/Geometry.h"
#include "Modules/Mesh.h"
#include "Modules/Material.h"

#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"

#include "Modules/Physics.h"

#include "Collision.h"

#include "AABB.h"
#include "BVH_Tree.h"

#include "GameModels.h"

#include "gtc/type_ptr.hpp"

#include "ShaderProgram.h"

#include "Modules/Light/DirectLight.h"
#include "Modules/Light/PointLight.h"
#include "Modules/Light/SpotLight.h"

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
GLFWwindow* Screen::GetWindow() {
    return Screen::_window;
}

Screen* Render::GetScreenClass() {
    return &(Render::_screenClass);
}

void Render::PrepareToRender() {
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    
    glEnable(GL_CULL_FACE); // enable culling face
    glCullFace(GL_BACK); // cull faces from back
    glFrontFace(GL_CCW); // vertex order (counter clock wise)
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_COLOR_MATERIAL);
    
    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LEQUAL);
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
    glLineWidth(World::DebugWireframThickness);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Render::RenderMesh(Mesh& mesh, std::shared_ptr<Camera> camera) {
    Render::SetMeshRenderOptions();

    if (mesh._material->_shader->GetCompiledStatus() == true) {
        glUseProgram(mesh._material->_shader->GetProgramId().value());
        glBindVertexArray(mesh._vao);

        mesh.ApplyMeshSettings(camera);

        glDrawElements(GL_TRIANGLES, mesh._indices->size(), GL_UNSIGNED_INT, mesh._indices->data());
        glBindVertexArray(0);
    }
}

void Render::RenderCollider(MeshCollider& collider, std::shared_ptr<Camera> camera) {
#ifdef _DEBUG
    Render::SetDebugRenderOptions();
    glColor3f(0.2, 0.8, 0.2);

    if (collider._debugMesh->_material->_shader->GetCompiledStatus() == true) {
        glUseProgram(collider._debugMesh->_material->_shader->GetProgramId().value());
        glBindVertexArray(collider._debugMesh->_vao);
        
        collider._debugMesh->ApplyMeshSettings(camera);
        
        glDrawElements(GL_TRIANGLES, collider._debugMesh->_indices->size(), GL_UNSIGNED_INT, collider._debugMesh->_indices->data());
        glBindVertexArray(0);
    }
#endif
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

void Render::SceneAssembler(std::shared_ptr<Camera> camera) {
    for (size_t i = 0; i < World::ObjectsOnScene.size(); i++)
    {
        for (size_t j = 0; j < World::ObjectsOnScene[i]->GetCountOfModules(); j++)
        {
            ModulesList type = World::ObjectsOnScene[i]->GetModuleByIndex(j)->GetType();

            if (type == MeshType) {
                std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(World::ObjectsOnScene[i]->GetModuleByIndex(j));
                //Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                Render::RenderMesh(*mesh, camera);
            }


#pragma region DebugRender
#ifdef _DEBUG
          if (World::DebugRenderEnabled == false)
              continue;
          
          std::shared_ptr<MeshCollider> collider = std::dynamic_pointer_cast<MeshCollider>(World::ObjectsOnScene[i]->GetModuleByIndex(j));
          
          if (collider != nullptr) {
              //Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                RenderCollider(*collider, camera);
              //RenderAABB(collider->_AABBvertex, collider->_AABBindices);
          }
          //
          //  std::shared_ptr<RigidBody> rb = std::dynamic_pointer_cast<RigidBody>(World::ObjectsOnScene[i]->GetModuleByIndex(j));
          //
          //  if (rb != nullptr) {
          //      Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
          //      RenderRigidBodyInfo(*rb);
          //  }
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
    //Render::ApplyCameraTransform(camera);

    //camera->SetCameraInfo(60, 16.0 / 9.0, 0.1, 300);
}

bool Render::CompileShaders() {
    return true;
}

void Render::RenderLoop(std::shared_ptr<Camera> camera) {
    if (!glfwWindowShouldClose(_screenClass._window))
    {
        glfwPollEvents();

        Render::ClearFrameBuffer();

        Render::PrepareToRender();
        //Render::ApplyCameraTransform(camera);

        Render::SceneAssembler(camera);
        //if (shader.GetCompiledStatus() == true) {
        //    //glUseProgram(shader.GetProgramId().value());
        //    //glBindVertexArray(vao);
        //    
        //    //glm::mat4x4 modelMat = glm::translate(glm::vec3(0, 0, 0));
        //    //shader.SetValue(ShadersType::VertexShader, "model_matrix", &modelMat);
        //    //
        //    //glm::mat4x4 viewMat = camera->_projectionMatrix * camera->_transformMatrix;
        //    //shader.SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));
        //
        //    glDrawArrays(GL_TRIANGLES, 0, 3);
        //}

        glFinish();
        glfwSwapBuffers(_screenClass._window);
    }
    else
    {
        exit(0);
    }
}
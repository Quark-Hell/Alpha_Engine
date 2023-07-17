#include "Graphic_Engine.h"

#include "World.h"
#include "Modules/Camera.h"
#include "Modules/Mesh.h"
#include "GameModels.h"

void Screen::CreateScreen(unsigned int Wight, unsigned int Height, unsigned int BitsPerPixel, std::string Name) {
    _wight = Wight;
    _height = Height;
    _bitsPerPixel = BitsPerPixel;
    _name = Name;

    //GLEW Init
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        //TODO: Add exception
        //std::cout << "Failed to initialize GLEW" << std::endl;
        //
    }

    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES,3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    ////Todo:
    ////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) if MacOs
    
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
    glfwSwapInterval(0);
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
    
    float ratio = 4 / 3;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.0f, 500.f);
}

void Render::ApplyCameraTransform(Camera* camera) {
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

void Render::RenderMesh(Mesh& mesh) {
    glColor3f(0.8, 0.8, 0.8);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    

    //glBindTexture();
    //glIndexPointer(GL_UNSIGNED_INT,0, mesh._indices);
    glNormalPointer(GL_FLOAT, 0, mesh._normals);
    glVertexPointer(3, GL_FLOAT, 0, mesh._vertex);
    
    glDrawElements(GL_TRIANGLES, mesh._indicesCount, GL_UNSIGNED_INT, mesh._indices);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Render::SceneAssembler() {
    for (size_t i = 0; i < World::ObjectsOnScene.size(); i++)
    {
        for (size_t j = 0; j < World::ObjectsOnScene[i]->GetCountOfModules(); j++)
        {
            Mesh* mesh = dynamic_cast<Mesh*>(World::ObjectsOnScene[i]->GetModuleByIndex(j));

            if (mesh != nullptr && mesh->GetType() == ModulesList::MeshType) {
                Render::ApplyTransformation(World::ObjectsOnScene[i]->GetPosition(), World::ObjectsOnScene[i]->GetRotation(), World::ObjectsOnScene[i]->GetScale());
                RenderMesh(*mesh);
            }
        }
    }   
}       

void Render::StartRender(Camera* camera) {
    //sf::ContextSettings window_settings;
    //window_settings.depthBits = 24;
    //window_settings.stencilBits = 8;
    //window_settings.antialiasingLevel = 2;

    _screenClass.CreateScreen(800, 600, 32, "GLFW OpenGL");

    int width, height;
    glfwGetFramebufferSize(_screenClass._window, &width, &height);
    glViewport(0, 0, width, height);

    Render::PrepareToRender();
    Render::ApplyCameraTransform(camera);

    camera->SetCameraInfo(60, 4.0 / 3.0, 0.1, 300);

    //_screenClass._screen->setVerticalSyncEnabled(true);
    //_screenClass._screen->setFramerateLimit(60);
}


void Render::RenderLoop(Camera* camera) {
    if (!glfwWindowShouldClose(_screenClass._window))
    {
        glfwPollEvents();

        Render::ClearFrameBuffer();

        Render::PrepareToRender();
        Render::ApplyCameraTransform(camera);

        Render::SceneAssembler();

        glfwSwapBuffers(_screenClass._window);
    }
    else
    {
        exit(0);
    }
}
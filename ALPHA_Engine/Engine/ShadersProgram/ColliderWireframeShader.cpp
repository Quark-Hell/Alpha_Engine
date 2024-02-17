#include "ColliderWireframeShader.h"

#include "World.h"

#include "Modules/Mesh.h"

ColliderWireframeShader::ColliderWireframeShader(Material* parentMat) : ShaderProgram(parentMat)
{
    ColliderWireframeShader::CreateShader("\\Shaders\\ColliderWireframeShaders\\VertexShader.txt", ShadersType::VertexShader);
    ColliderWireframeShader::CreateShader("\\Shaders\\ColliderWireframeShaders\\FragmentShader.txt", ShadersType::FragmentShader);

    ColliderWireframeShader::InitShader();
}

ColliderWireframeShader::~ColliderWireframeShader()
{
}

void ColliderWireframeShader::ApplyShadersSettings(std::shared_ptr<Camera> camera)
{
    glm::mat4x4 viewMat = camera->GetProjectionMatrix() * camera->GetTransformMatrix();
    ColliderWireframeShader::SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));

    ColliderWireframeShader::SetValue(ShadersType::VertexShader, "model_matrix", &ColliderWireframeShader::GetParentMaterial()->GetParentMesh()->GetTransformMatrix());


    //DebugMesh::_material->_shader->SetValue(ShadersType::VertexShader, "color", &World::DebugWireframeColor);
}

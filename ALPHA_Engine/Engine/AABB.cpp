#include "AABB.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShadersProgram/ColliderWireframeShader.h"
#include "Object.h"

AABB::AABB() {
#ifdef _DEBUG
    _AABBMesh->_material->Shader = std::make_shared<ColliderWireframeShader>(_AABBMesh->_material.get());
    ColliderWireframeShader* shader = reinterpret_cast<ColliderWireframeShader*>(_AABBMesh->_material->Shader.get());
    shader->color = Vector3(0.812, 0.812, 0.812);
    AABB::CreateAABB();
#endif // _DEBUG

    std::cout << "create\n";
}

AABB::AABB(Object& parentObject) {
    AABB::SetSize(parentObject.GetScale());
    AABB::_position = parentObject.GetPosition();
    AABB::_originPos = parentObject.GetOriginPosition();

#ifdef _DEBUG
    _AABBMesh->_material->Shader = std::make_shared<ColliderWireframeShader>(_AABBMesh->_material.get());
    AABB::CreateAABB();
#endif // _DEBUG

    std::cout << "create\n";
}

AABB::~AABB() {

}

#ifdef _DEBUG
void AABB::CreateAABB() {
    _AABBMesh->InsertVertex(Vector3(-1, -1, 1), 0, true);
    _AABBMesh->InsertVertex(Vector3(-1, 1, 1), 1, true);

    _AABBMesh->InsertVertex(Vector3(-1, 1, 1), 2, true);
    _AABBMesh->InsertVertex(Vector3(1, 1, 1), 3, true);

    _AABBMesh->InsertVertex(Vector3(1, 1, 1), 4, true);
    _AABBMesh->InsertVertex(Vector3(1, -1, 1), 5, true);

    _AABBMesh->InsertVertex(Vector3(1, -1, 1), 6, true);
    _AABBMesh->InsertVertex(Vector3(-1, -1, 1), 7, true);

    _AABBMesh->InsertVertex(Vector3(-1, -1, 1), 8, true);
    _AABBMesh->InsertVertex(Vector3(-1, -1, -1), 9, true);

    _AABBMesh->InsertVertex(Vector3(-1, -1, -1), 10, true);
    _AABBMesh->InsertVertex(Vector3(-1, 1, -1), 11, true);

    _AABBMesh->InsertVertex(Vector3(-1, 1, -1), 12, true);
    _AABBMesh->InsertVertex(Vector3(-1, 1, 1), 13, true);

    _AABBMesh->InsertVertex(Vector3(-1, 1, -1), 14, true);
    _AABBMesh->InsertVertex(Vector3(1, 1, -1), 15, true);

    _AABBMesh->InsertVertex(Vector3(1, 1, -1), 16, true);
    _AABBMesh->InsertVertex(Vector3(1, -1, -1), 17, true);

    _AABBMesh->InsertVertex(Vector3(1, -1, -1), 18, true);
    _AABBMesh->InsertVertex(Vector3(-1, -1, -1), 19, true);

    _AABBMesh->InsertVertex(Vector3(1, -1, -1), 20, true);
    _AABBMesh->InsertVertex(Vector3(1, -1, 1), 21, true);

    _AABBMesh->InsertVertex(Vector3(1, 1, -1), 22, true);
    _AABBMesh->InsertVertex(Vector3(1, 1, 1), 23, true);

    _AABBMesh->SetPosition(0, 0, 0);
    _AABBMesh->SetScale(1, 1, 1);
}

#endif // _DEBUG

void AABB::SetSize(Vector3 scale){
 
#ifdef _DEBUG
    AABB::_scale = scale;
    AABB::_AABBMesh->SetScale(AABB::_scale);

#endif // _DEBUG
}

Vector3 AABB::GetSize() {
    return AABB::_scale;
}

Vector3 AABB::GetAABBPosition() {
    return _position;
}

void AABB::UpdateAABB(Object& parentObject) {
    AABB::SetSize(parentObject.GetScale());
    AABB::_position = parentObject.GetPosition();
    AABB::_originPos = parentObject.GetOriginPosition();

#ifdef _DEBUG
    AABB::ApplyTransformation(parentObject);
    AABB::_AABBMesh->SetPosition(AABB::_position);
#endif // _DEBUG
}

void AABB::ApplyTransformation(Object& parentObject)
{
	Vector4 parentRotation = parentObject.GetRotation();
	Vector3 parentPosition = parentObject.GetPosition();
	Vector3 parentScale = parentObject.GetScale();
	Vector3 parentOrigin = parentObject.GetOriginPosition();

	glm::mat4x4 parentRotMat(1.0f);

	const float parentRadX = M_PI / 180 * parentRotation.X;
	const float parentRadY = M_PI / 180 * parentRotation.Y;
	const float parentRadZ = M_PI / 180 * parentRotation.Z;

	parentRotMat = glm::rotate(parentRotMat, parentRadX, glm::vec3(1.0f, 0.0f, 0.0f));
	parentRotMat = glm::rotate(parentRotMat, parentRadY, glm::vec3(0.0f, 1.0f, 0.0f));
	parentRotMat = glm::rotate(parentRotMat, parentRadZ, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4x4 transMat(1.0f);
	transMat = glm::translate(glm::vec3(
		AABB::_position.X ,
		AABB::_position.Y ,
		AABB::_position.Z ));

	glm::mat4x4 parentOriginMat(1.0f);
	parentOriginMat = glm::translate(parentOriginMat, glm::vec3(
		-parentOrigin.X,
		-parentOrigin.Y,
		-parentOrigin.Z));

	glm::mat4x4 backParentOriginMat(1.0f);
	backParentOriginMat = glm::translate(backParentOriginMat, glm::vec3(
		parentOrigin.X,
		parentOrigin.Y,
		parentOrigin.Z));


    glm::mat4x4 rotMat = backParentOriginMat * parentRotMat * parentOriginMat;

	glm::mat4x4 _transformMatrix = transMat * rotMat;


    glm::vec4 pos = glm::vec4(0, 0, 0, 1);
    pos = _transformMatrix * pos;

    AABB::_position = Vector3(pos.x, pos.y, pos.z);
    std::cout << "X: " << AABB::_position.X << " Y: " << AABB::_position.Y << " Z: " << AABB::_position.Z << "\n";
}

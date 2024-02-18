#include "PathShader.h"
#include "Modules/Material.h"

PathShader::PathShader(Material* parentMat) : ShaderProgram(parentMat) {
	PathShader::points.resize(PathShader::maxPoints);
}

PathShader::~PathShader() {

}

void PathShader::ApplyShadersSettings(std::shared_ptr<Camera> camera) {
	glm::mat4x4 viewMat = camera->GetProjectionMatrix() * camera->GetTransformMatrix();
	PathShader::SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));
}

void PathShader::AddPoint(Vector3 point)
{
	if (PathShader::GetParentMaterial() == nullptr)
		return;

	if (PathShader::GetParentMaterial()->GetParentMesh() == nullptr)
		return;

	pointsCount++;
	if (PathShader::pointsCount >= 500) {
		pointsCount = 0;
	}

	PathShader::points[pointsCount] = point;

	PathShader::GetParentMaterial()->GetParentMesh()->InsertVertex(PathShader::points[pointsCount], pointsCount, true);
}
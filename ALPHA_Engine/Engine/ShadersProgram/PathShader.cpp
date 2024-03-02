#include "PathShader.h"
#include "Modules/Material.h"

PathShader::PathShader(Material* parentMat) : ShaderProgram(parentMat) {
	PathShader::CreateShader("\\Shaders\\PathShader\\VertexShader.txt", ShadersType::VertexShader);
	PathShader::CreateShader("\\Shaders\\PathShader\\FragmentShader.txt", ShadersType::FragmentShader);

	PathShader::InitShader();

	PathShader::RenderMode = RenderModes::LineStip;
}

PathShader::~PathShader() {

}

void PathShader::ApplyShadersSettings(std::shared_ptr<Camera> camera) {
	glm::mat4x4 viewMat = camera->GetProjectionMatrix() * camera->GetTransformMatrix();
	PathShader::SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));

	PathShader::SetValue(ShadersType::FragmentShader, "color", Vector3(0.839, 0.839, 0.839));

	glm::mat4x4 mat = glm::mat4x4(1.0f);
	glm::mat4x4 scaleMat(1.0f);
	scaleMat = glm::scale(scaleMat, glm::vec3(
		1,
		1,
		1));
	PathShader::SetValue(ShadersType::VertexShader, "model_matrix", &(scaleMat));

	glPolygonMode(GL_FRONT, GL_LINE_LOOP);
	glLineWidth(PathShader::LineWidth);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
}

void PathShader::AddPoint(Vector3 point)
{
	if (PathShader::GetParentMaterial() == nullptr)
		return;

	if (PathShader::GetParentMaterial()->GetParentMesh() == nullptr)
		return;

	pointsCount++;
	if (PathShader::pointsCount >= PathShader::maxPoints) {
		PathShader::isOverflow = true;
	}
	if (PathShader::isOverflow) {
		pointsCount = PathShader::maxPoints - 1;
		PathShader::GetParentMaterial()->GetParentMesh()->ShiftVertexArray(-1);
	}
	PathShader::GetParentMaterial()->GetParentMesh()->InsertVertex(point, pointsCount, true);
}
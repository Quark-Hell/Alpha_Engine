#pragma once
#include "Basical_Type.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include "Modules/Camera.h"

#include "Texture.h"
#include "TextureLoader.h"

class Material;

enum ShadersType {
	VertexShader = 0,
	TessellationControlShader = 1,
	TessellationEvaluationShader = 2,
	GeometryShader = 3,
	FragmentShader = 4,
	ComputeShader = 5,
};

enum TypeOfOpaqueTextuere {
	Diffuse = 0,
	Metallic = 1,
	Specular = 2,
	Roughness = 3,
	Anisotropic = 4,
	Emission = 5,
	NormalsMap = 6,
	OpacityMap = 7,
	OcclusionMap = 8
};

enum RenderModes {
	Points = 0,
	LineStip = 1,
	LineLoop = 2,
	Lines = 3,
	LineStripAdjacency = 4,
	LinesAdjacency = 5,
	TriangleStrip = 6,
	TriangleFan = 7,
	Triangles = 8,
	TriangleStripAdjacency = 9,
	TrianglesAdjacency = 10,
	Patches = 11,
};

class ShaderProgram
{
private:
	unsigned int _vertexShaderId = 0;
	unsigned int _tessellationControlShaderId = 0;
	unsigned int _tessellationEvaluationShaderId = 0;
	unsigned int _geometryShaderId = 0;
	unsigned int _fragmentShaderId = 0;
	unsigned int _computeShaderId = 0;

	unsigned int _programId = 0;
	bool _isCompiled = false;

	std::shared_ptr<std::string> _vertexShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _tessellationControlShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _tessellationEvaluationShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _geometryShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _fragmentShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _computeShaderSource = std::make_shared<std::string>();
	
	Material* _parentMaterial;

protected:
	RenderModes RenderMode = RenderModes::Triangles;

public:
	ShaderProgram(Material* parentMat);
	virtual ~ShaderProgram();

	ShaderProgram& operator=(ShaderProgram&& shaderProgram);

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void SetParent(Material& material);

#pragma region Interface
	unsigned int GetVertexShaderId();
	unsigned int GetTesselationControlShaderId();
	unsigned int GetTesselationEvaluationShaderId();
	unsigned int GetGeometryShaderId();
	unsigned int GetFragmentShaderId();
	unsigned int GetComputeShaderId();

	unsigned int GetProgramId();
	bool GetCompiledStatus();

	Material* GetParentMaterial();

	template <typename T, typename = std::enable_if_t<
		std::is_same<glm::mat4x4, T>::value ||
		std::is_same<glm::mat3x3, T>::value ||
		std::is_same<int, T>::value ||
		std::is_same<unsigned int, T>::value ||
		std::is_same<float, T>::value ||
		std::is_same<Vector3, T>::value
	>>
		inline void SetValue(ShadersType shaderType, std::string fieldName, T* value) {
		if (ShaderProgram::_programId == 0)
			return;

		if (std::is_same<glm::mat4x4, T>::value) {
			glm::mat4x4* v = reinterpret_cast<glm::mat4x4*>(value);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same<glm::mat3x3, T>::value) {
			glm::mat3x3* v = reinterpret_cast<glm::mat3x3*>(value);
			glUniformMatrix3fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same<int, T>::value) {
			int* v = reinterpret_cast<int*>(value);
			glUniform1i(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same<unsigned int, T>::value) {
			unsigned int* v = reinterpret_cast<unsigned int*>(value);
			glUniform1ui(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same<float, T>::value) {
			float* v = reinterpret_cast<float*>(value);
			glUniform1f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same<Vector3, T>::value) {
			Vector3* v = reinterpret_cast<Vector3*>(value);
			glUniform3f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), v->X, v->Y, v->Z);
		}
	}

#pragma endregion

	bool CreateShader(const char* sourcePath, ShadersType shaderType);
	bool InitShader();

	bool Bind();
	bool Unbind();

	bool CompileShader();

	bool AttachShader();
	bool AttachShader(ShadersType shaderType);

	void DetachShader();
	void DetachShader(ShadersType shaderType);

	void DeleteShaders();
	void DeleteShader(ShadersType shaderType);

	virtual bool LoadTexture(TypeOfOpaqueTextuere typeOfTexture, std::string pathToTexture);
	virtual bool AsyncLoadTexture(TypeOfOpaqueTextuere typeOfTexture, std::string pathToTexture);

protected:
	virtual void ApplyShadersSettings(std::shared_ptr<Camera> camera);

	friend class Render;
	friend class Material;
};


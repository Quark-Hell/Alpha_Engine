#pragma once
#include "Basical_Type.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "Modules/Material.h"
#include "Modules/Camera.h"

enum ShadersType {
	VertexShader = 0,
	TessellationControlShader = 1,
	TessellationEvaluationShader = 2,
	GeometryShader = 3,
	FragmentShader = 4,
	ComputeShader = 5,
};

class ShaderProgram
{
private:
	std::optional<unsigned int> _vertexShaderId = std::nullopt;
	std::optional<unsigned int> _tessellationControlShaderId = std::nullopt;
	std::optional<unsigned int> _tessellationEvaluationShaderId = std::nullopt;
	std::optional<unsigned int> _geometryShaderId = std::nullopt;
	std::optional<unsigned int> _fragmentShaderId = std::nullopt;
	std::optional<unsigned int> _computeShaderId = std::nullopt;

	std::shared_ptr<std::string> _vertexShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _tessellationControlShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _tessellationEvaluationShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _geometryShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _fragmentShaderSource = std::make_shared<std::string>();
	std::shared_ptr<std::string> _computeShaderSource = std::make_shared<std::string>();
		
	std::optional<unsigned int> _programId = std::nullopt;

	bool _isCompiled = false;

	Material* _parentMaterial;

public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram& operator=(ShaderProgram&& shaderProgram);

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

#pragma region Interface
	std::optional<unsigned int> GetVertexShaderId();
	std::optional<unsigned int> GetTesselationControlShaderId();
	std::optional<unsigned int> GetTesselationEvaluationShaderId();
	std::optional<unsigned int> GetGeometryShaderId();
	std::optional<unsigned int> GetFragmentShaderId();
	std::optional<unsigned int> GetComputeShaderId();

	std::optional<unsigned int> GetProgramId();
	bool GetCompiledStatus();

	template <typename T, typename = std::enable_if_t<
		std::is_same<glm::mat4x4, T>::value ||
		std::is_same<glm::mat3x3, T>::value ||
		std::is_same<int, T>::value ||
		std::is_same<unsigned int, T>::value ||
		std::is_same<float, T>::value ||
		std::is_same<Vector3, T>::value
	>>
		inline void SetValue(ShadersType shaderType, std::string fieldName, T* value) {
		if (ShaderProgram::_programId == std::nullopt)
			return;

		if (std::is_same<glm::mat4x4, T>::value) {
			glm::mat4x4* v = reinterpret_cast<glm::mat4x4*>(value);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same<glm::mat3x3, T>::value) {
			glm::mat3x3* v = reinterpret_cast<glm::mat3x3*>(value);
			glUniformMatrix3fv(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same<int, T>::value) {
			int* v = reinterpret_cast<int*>(value);
			glUniform1i(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), *v);
		}
		else if (std::is_same<unsigned int, T>::value) {
			unsigned int* v = reinterpret_cast<unsigned int*>(value);
			glUniform1ui(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), *v);
		}
		else if (std::is_same<float, T>::value) {
			float* v = reinterpret_cast<float*>(value);
			glUniform1f(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), *v);
		}
		else if (std::is_same<Vector3, T>::value) {
			Vector3* v = reinterpret_cast<Vector3*>(value);
			glUniform3f(glGetUniformLocation(ShaderProgram::_programId.value(), fieldName.c_str()), v->X, v->Y, v->Z);
		}
	}

#pragma endregion

	bool CreateShader(const char* sourcePath, ShadersType shaderType);
	bool Bind();
	bool Unbind();

	bool CompileShader();

	bool AttachShader();
	bool AttachShader(ShadersType shaderType);

	void DetachShader();
	void DetachShader(ShadersType shaderType);

	void DeleteShader();
	void DeleteShader(ShadersType shaderType);

public:
	void virtual ApplyShadersValue();

private:
	void ApplyShadersSettings(std::shared_ptr<Camera> camera);

	friend class Material;
};


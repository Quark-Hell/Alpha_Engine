#pragma once
#include "Basical_Type.h"

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

	template <typename T> 
	void SetValue(ShadersType shaderType, std::string fieldName, T value);

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

	friend class ShaderManager;
};

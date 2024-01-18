#include "ShaderProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
	if (ShaderProgram::_programId != std::nullopt)
		glDeleteProgram(ShaderProgram::_programId.value());
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram)
{
	if(ShaderProgram::_programId != std::nullopt)
		glDeleteProgram(ShaderProgram::_programId.value());

	ShaderProgram::_programId = shaderProgram._programId;

	shaderProgram._programId = 0;
	shaderProgram._isCompiled = false;
	return *this;
}

std::optional<unsigned int> ShaderProgram::GetVertexShaderId()
{
	return ShaderProgram::_vertexShaderId;
}

std::optional<unsigned int> ShaderProgram::GetTesselationControlShaderId()
{
	return ShaderProgram::_tessellationControlShaderId;
}

std::optional<unsigned int> ShaderProgram::GetTesselationEvaluationShaderId()
{
	return ShaderProgram::_tessellationEvaluationShaderId;
}

std::optional<unsigned int> ShaderProgram::GetGeometryShaderId()
{
	return ShaderProgram::_geometryShaderId;
}

std::optional<unsigned int> ShaderProgram::GetFragmentShaderId()
{
	return ShaderProgram::_fragmentShaderId;
}

std::optional<unsigned int> ShaderProgram::GetComputeShaderId()
{
	return ShaderProgram::_computeShaderId;
}

std::optional<unsigned int> ShaderProgram::GetProgramId()
{
	return ShaderProgram::_programId;
}

bool ShaderProgram::GetCompiledStatus()
{
	return ShaderProgram::_isCompiled;
}

//TODO: Create all types of shader
bool ShaderProgram::CreateShader(const char* sourcePath, ShadersType shaderType)
{
	unsigned int shaderId;

	auto readShaderSource = [](const char* path, std::shared_ptr<std::string> str) {
		std::string genPath = std::filesystem::current_path().string() + path;
		std::ifstream sourceStream(genPath);

		std::string* source = new std::string();

		if (sourceStream.is_open()) {
			std::string line;
			while (std::getline(sourceStream, line)) {
				*str.get() += line + "\n";
			}
		}
		else {
			std::cerr << "Unable to open file: " << path << std::endl;
			return false;
		}

		sourceStream.close();
		};

	const char* chSource;

	switch (shaderType)
	{
	case VertexShader:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_vertexShaderSource))
			return false;

		chSource = ShaderProgram::_vertexShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);
		_vertexShaderId = shaderId;
		break;
	case TessellationControlShader:
		//unsigned int shader_id = glCreateShader(shaderType);
		return false;
	case TessellationEvaluationShader:
		//unsigned int shader_id = glCreateShader(shaderType);
		return false;
	case GeometryShader:
		//unsigned int shader_id = glCreateShader(shaderType);
		return false;
	case FragmentShader:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_fragmentShaderSource))
			return false;

		chSource = ShaderProgram::_fragmentShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);
		_fragmentShaderId = shaderId;
		break;
	case ComputeShader:
		//unsigned int shader_id = glCreateShader(shaderType);
		return false;
	default:
		return false;
	}

	return true;
}

bool ShaderProgram::Bind()
{
	if (_isCompiled == false)
		return false;

	if (_programId == std::nullopt)
		return false;

	glUseProgram(_programId.value());
	return true;
}

bool ShaderProgram::Unbind()
{
	glUseProgram(0);
	return true;
}

bool ShaderProgram::CompileShader()
{
	auto TryCompile = [](unsigned int shaderId, bool& compiledStatus) {
		int success;

		glCompileShader(shaderId);
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			char info_log[1024];
			glGetShaderInfoLog(shaderId, 1024, nullptr, info_log);

			std::cout << "Shader compilation error:\n" << info_log;

			compiledStatus = false;
			return false;
		}
		compiledStatus = true;
		return true;
	};

	bool successCompile = false;

	if (_vertexShaderId != std::nullopt)
		if (!(successCompile = TryCompile(ShaderProgram::_vertexShaderId.value(), ShaderProgram::_isCompiled)))
			return false;
	
	if (_tessellationControlShaderId != std::nullopt)
		if (!(TryCompile(ShaderProgram::_tessellationControlShaderId.value(), ShaderProgram::_isCompiled)))
			return false;

	if (_tessellationEvaluationShaderId != std::nullopt)
		if (!(TryCompile(ShaderProgram::_tessellationEvaluationShaderId.value(), ShaderProgram::_isCompiled)))
			return false;
	
	if (_geometryShaderId != std::nullopt)
		if (!(TryCompile(ShaderProgram::_geometryShaderId.value(), ShaderProgram::_isCompiled)))
			return false;
	
	if (_fragmentShaderId != std::nullopt)
		if (!(TryCompile(ShaderProgram::_fragmentShaderId.value(), ShaderProgram::_isCompiled)))
			return false;
	
	if (_computeShaderId != std::nullopt)
		if (!(TryCompile(ShaderProgram::_computeShaderId.value(), ShaderProgram::_isCompiled)))
			return false;
	
	return true;
}

bool ShaderProgram::AttachShader()
{
	if (ShaderProgram::_isCompiled == false)
		return false;

	ShaderProgram::_programId = glCreateProgram();

	if (_vertexShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_vertexShaderId.value());

	if (_tessellationControlShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_tessellationControlShaderId.value());

	if (_tessellationEvaluationShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_tessellationEvaluationShaderId.value());

	if (_geometryShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_geometryShaderId.value());

	if (_fragmentShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_fragmentShaderId.value());

	if (_computeShaderId != std::nullopt)
		glAttachShader(ShaderProgram::_programId.value(), ShaderProgram::_computeShaderId.value());

	glLinkProgram(ShaderProgram::_programId.value());
	return true;
}

void ShaderProgram::DetachShader()
{
	if (_programId != std::nullopt) {
		if (_vertexShaderId != std::nullopt)
			glDetachShader(_programId.value(), _vertexShaderId.value());

		if (_tessellationControlShaderId != std::nullopt)
			glDetachShader(_programId.value(), _tessellationControlShaderId.value());

		if (_tessellationEvaluationShaderId != std::nullopt)
			glDetachShader(_programId.value(), _tessellationEvaluationShaderId.value());

		if (_geometryShaderId != std::nullopt)
			glDetachShader(_programId.value(), _geometryShaderId.value());

		if (_fragmentShaderId != std::nullopt)
			glDetachShader(_programId.value(), _fragmentShaderId.value());

		if (_computeShaderId != std::nullopt)
			glDetachShader(_programId.value(), _computeShaderId.value());
	}
}

void ShaderProgram::DeleteShader()
{
	if (_vertexShaderId != std::nullopt)
		glDeleteShader(_vertexShaderId.value());

	if (_tessellationControlShaderId != std::nullopt)
		glDeleteShader(_tessellationControlShaderId.value());

	if (_tessellationEvaluationShaderId != std::nullopt)
		glDeleteShader(_tessellationEvaluationShaderId.value());

	if (_geometryShaderId != std::nullopt)
		glDeleteShader(_geometryShaderId.value());

	if (_fragmentShaderId != std::nullopt)
		glDeleteShader(_fragmentShaderId.value());

	if (_computeShaderId != std::nullopt)
		glDeleteShader(_computeShaderId.value());
}

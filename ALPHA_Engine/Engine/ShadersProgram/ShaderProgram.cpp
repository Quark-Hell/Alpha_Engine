#include "ShaderProgram.h"

#include "Modules/Light/DirectLight.h"
#include "Modules/Light/PointLight.h"
#include "Modules/Light/SpotLight.h"

#include "Modules/Mesh.h"

ShaderProgram::ShaderProgram(Material* parentMat)
{
	ShaderProgram::_parentMaterial = parentMat;
}

ShaderProgram::~ShaderProgram()
{
	ShaderProgram::DeleteShaders();

	if (ShaderProgram::_programId != 0)
		glDeleteProgram(ShaderProgram::_programId);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram)
{
	if(ShaderProgram::_programId != 0)
		glDeleteProgram(ShaderProgram::_programId);

	ShaderProgram::_programId = shaderProgram._programId;

	shaderProgram._programId = 0;
	shaderProgram._isCompiled = false;
	return *this;
}

void ShaderProgram::SetParent(Material& material)
{
	ShaderProgram::_parentMaterial = &material;
}

unsigned int ShaderProgram::GetVertexShaderId()
{
	return ShaderProgram::_vertexShaderId;
}

unsigned int ShaderProgram::GetTesselationControlShaderId()
{
	return ShaderProgram::_tessellationControlShaderId;
}

unsigned int ShaderProgram::GetTesselationEvaluationShaderId()
{
	return ShaderProgram::_tessellationEvaluationShaderId;
}

unsigned int ShaderProgram::GetGeometryShaderId()
{
	return ShaderProgram::_geometryShaderId;
}

unsigned int ShaderProgram::GetFragmentShaderId()
{
	return ShaderProgram::_fragmentShaderId;
}

unsigned int ShaderProgram::GetComputeShaderId()
{
	return ShaderProgram::_computeShaderId;
}

unsigned int ShaderProgram::GetProgramId()
{
	return ShaderProgram::_programId;
}

bool ShaderProgram::GetCompiledStatus()
{
	return ShaderProgram::_isCompiled;
}

Material* ShaderProgram::GetParentMaterial()
{
	return ShaderProgram::_parentMaterial;
}

//template <typename T, typename>
//void ShaderProgram::SetValue(ShadersType shaderType, std::string fieldName, T value) {
//
//}

bool ShaderProgram::CreateShader(const char* sourcePath, ShadersType shaderType)
{
	unsigned int shaderId;

	auto readShaderSource = [](const char* path, std::shared_ptr<std::string> str) {
		std::string genPath = std::filesystem::current_path().string() + path;
		std::ifstream sourceStream(genPath);

		if (sourceStream.is_open()) {
			str.get()->clear();
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
		return true;
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
		shaderId = glCreateShader(GL_TESS_CONTROL_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_tessellationControlShaderSource))
			return false;

		chSource = ShaderProgram::_tessellationControlShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);

		_tessellationControlShaderId = shaderId;
		break;

	case TessellationEvaluationShader:
		shaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_tessellationEvaluationShaderSource))
			return false;

		chSource = ShaderProgram::_tessellationEvaluationShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);

		_tessellationEvaluationShaderId = shaderId;
		break;

	case GeometryShader:
		shaderId = glCreateShader(GL_GEOMETRY_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_geometryShaderSource))
			return false;

		chSource = ShaderProgram::_geometryShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);

		_geometryShaderId = shaderId;
		break;

	case FragmentShader:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_fragmentShaderSource))
			return false;

		chSource = ShaderProgram::_fragmentShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);
		_fragmentShaderId = shaderId;
		break;
	case ComputeShader:
		shaderId = glCreateShader(GL_COMPUTE_SHADER);
		if (!readShaderSource(sourcePath, ShaderProgram::_computeShaderSource))
			return false;

		chSource = ShaderProgram::_computeShaderSource.get()->c_str();
		glShaderSource(shaderId, 1, &chSource, nullptr);
		_computeShaderId = shaderId;
		break;
	default:
		return false;
	}

	_isCompiled = false;
	return true;
}

bool ShaderProgram::InitShader()
{
	ShaderProgram::CompileShader();

	if (ShaderProgram::GetCompiledStatus()) {
		ShaderProgram::AttachShader();
		ShaderProgram::DeleteShaders();
	}
	else {
		ShaderProgram::DeleteShaders();
		return false;
	}

	return true;
}

bool ShaderProgram::Bind()
{
	if (_isCompiled == false)
		return false;

	if (_programId == 0)
		return false;

	glUseProgram(_programId);
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

	if (_vertexShaderId != 0)
		if (!(successCompile = TryCompile(ShaderProgram::_vertexShaderId, ShaderProgram::_isCompiled)))
			return false;
	
	if (_tessellationControlShaderId != 0)
		if (!(TryCompile(ShaderProgram::_tessellationControlShaderId, ShaderProgram::_isCompiled)))
			return false;

	if (_tessellationEvaluationShaderId != 0)
		if (!(TryCompile(ShaderProgram::_tessellationEvaluationShaderId, ShaderProgram::_isCompiled)))
			return false;
	
	if (_geometryShaderId != 0)
		if (!(TryCompile(ShaderProgram::_geometryShaderId, ShaderProgram::_isCompiled)))
			return false;
	
	if (_fragmentShaderId != 0)
		if (!(TryCompile(ShaderProgram::_fragmentShaderId, ShaderProgram::_isCompiled)))
			return false;
	
	if (_computeShaderId != 0)
		if (!(TryCompile(ShaderProgram::_computeShaderId, ShaderProgram::_isCompiled)))
			return false;
	
	return true;
}

bool ShaderProgram::AttachShader()
{
	if (ShaderProgram::_isCompiled == false)
		return false;

	ShaderProgram::_programId = glCreateProgram();

	if (_vertexShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_vertexShaderId);

	if (_tessellationControlShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_tessellationControlShaderId);

	if (_tessellationEvaluationShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_tessellationEvaluationShaderId);

	if (_geometryShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_geometryShaderId);

	if (_fragmentShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_fragmentShaderId);

	if (_computeShaderId != 0)
		glAttachShader(ShaderProgram::_programId, ShaderProgram::_computeShaderId);

	glLinkProgram(ShaderProgram::_programId);
	return true;
}

void ShaderProgram::DetachShader()
{
	if (_programId != 0) {
		if (_vertexShaderId != 0)
			glDetachShader(_programId, _vertexShaderId);

		if (_tessellationControlShaderId != 0)
			glDetachShader(_programId, _tessellationControlShaderId);

		if (_tessellationEvaluationShaderId != 0)
			glDetachShader(_programId, _tessellationEvaluationShaderId);

		if (_geometryShaderId != 0)
			glDetachShader(_programId, _geometryShaderId);

		if (_fragmentShaderId != 0)
			glDetachShader(_programId, _fragmentShaderId);

		if (_computeShaderId != 0)
			glDetachShader(_programId, _computeShaderId);
	}
}

void ShaderProgram::DeleteShaders()
{
	if (ShaderProgram::_vertexShaderId != 0)
		glDeleteShader(_vertexShaderId);

	if (ShaderProgram::_tessellationControlShaderId != 0)
		glDeleteShader(_tessellationControlShaderId);

	if (ShaderProgram::_tessellationEvaluationShaderId != 0)
		glDeleteShader(_tessellationEvaluationShaderId);

	if (ShaderProgram::_geometryShaderId != 0)
		glDeleteShader(_geometryShaderId);

	if (ShaderProgram::_fragmentShaderId != 0)
		glDeleteShader(_fragmentShaderId);

	if (ShaderProgram::_computeShaderId != 0)
		glDeleteShader(_computeShaderId);

	ShaderProgram::_vertexShaderSource->clear();
	ShaderProgram::_tessellationControlShaderSource->clear();
	ShaderProgram::_tessellationEvaluationShaderSource->clear();
	ShaderProgram::_geometryShaderSource->clear();
	ShaderProgram::_fragmentShaderSource->clear();
	ShaderProgram::_computeShaderSource->clear();
}

void ShaderProgram::DeleteShader(ShadersType shaderType)
{
	switch (shaderType)
	{
	case VertexShader:
		if (ShaderProgram::_vertexShaderId != 0)
			glDeleteShader(_vertexShaderId);

		ShaderProgram::_vertexShaderSource->clear();
		break;

	case TessellationControlShader:
		if (ShaderProgram::_tessellationControlShaderId != 0)
			glDeleteShader(_tessellationControlShaderId);

		ShaderProgram::_tessellationControlShaderSource->clear();
		break;

	case TessellationEvaluationShader:
		if (ShaderProgram::_tessellationEvaluationShaderId != 0)
			glDeleteShader(_tessellationEvaluationShaderId);

		ShaderProgram::_tessellationEvaluationShaderSource->clear();
		break;

	case GeometryShader:
		if (ShaderProgram::_geometryShaderId != 0)
			glDeleteShader(_geometryShaderId);

		ShaderProgram::_geometryShaderSource->clear();
		break;

	case FragmentShader:
		if (ShaderProgram::_fragmentShaderId != 0)
			glDeleteShader(_fragmentShaderId);

		ShaderProgram::_fragmentShaderSource->clear();
		break;

	case ComputeShader:
		if (ShaderProgram::_computeShaderId != 0)
			glDeleteShader(_computeShaderId);

		ShaderProgram::_computeShaderSource->clear();
	default:
		return;
	}
}

bool ShaderProgram::LoadTexture(TypeOfOpaqueTextuere typeOfTexture, std::string pathToTexture)
{
	return false;
}

bool ShaderProgram::AsyncLoadTexture(TypeOfOpaqueTextuere typeOfTexture, std::string pathToTexture)
{
	return false;
}

void ShaderProgram::ApplyShadersSettings(std::shared_ptr<Camera> camera)
{

}

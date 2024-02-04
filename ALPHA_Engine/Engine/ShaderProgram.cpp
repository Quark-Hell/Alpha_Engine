#include "ShaderProgram.h"

#include "Modules/Light/DirectLight.h"
#include "Modules/Light/PointLight.h"
#include "Modules/Light/SpotLight.h"

#include "Modules/Mesh.h"

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

void ShaderProgram::DeleteShaders()
{
	if (ShaderProgram::_vertexShaderId != std::nullopt)
		glDeleteShader(_vertexShaderId.value());

	if (ShaderProgram::_tessellationControlShaderId != std::nullopt)
		glDeleteShader(_tessellationControlShaderId.value());

	if (ShaderProgram::_tessellationEvaluationShaderId != std::nullopt)
		glDeleteShader(_tessellationEvaluationShaderId.value());

	if (ShaderProgram::_geometryShaderId != std::nullopt)
		glDeleteShader(_geometryShaderId.value());

	if (ShaderProgram::_fragmentShaderId != std::nullopt)
		glDeleteShader(_fragmentShaderId.value());

	if (ShaderProgram::_computeShaderId != std::nullopt)
		glDeleteShader(_computeShaderId.value());

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
		if (ShaderProgram::_vertexShaderId != std::nullopt)
			glDeleteShader(_vertexShaderId.value());

		ShaderProgram::_vertexShaderSource->clear();
		break;

	case TessellationControlShader:
		if (ShaderProgram::_tessellationControlShaderId != std::nullopt)
			glDeleteShader(_tessellationControlShaderId.value());

		ShaderProgram::_tessellationControlShaderSource->clear();
		break;

	case TessellationEvaluationShader:
		if (ShaderProgram::_tessellationEvaluationShaderId != std::nullopt)
			glDeleteShader(_tessellationEvaluationShaderId.value());

		ShaderProgram::_tessellationEvaluationShaderSource->clear();
		break;

	case GeometryShader:
		if (ShaderProgram::_geometryShaderId != std::nullopt)
			glDeleteShader(_geometryShaderId.value());

		ShaderProgram::_geometryShaderSource->clear();
		break;

	case FragmentShader:
		if (ShaderProgram::_fragmentShaderId != std::nullopt)
			glDeleteShader(_fragmentShaderId.value());

		ShaderProgram::_fragmentShaderSource->clear();
	case ComputeShader:
		if (ShaderProgram::_computeShaderId != std::nullopt)
			glDeleteShader(_computeShaderId.value());

		ShaderProgram::_computeShaderSource->clear();
	default:
		return;
	}
}

void ShaderProgram::ApplyShadersValue()
{
}

void ShaderProgram::ApplyShadersSettings(std::shared_ptr<Camera> camera)
{
	int ambientLightsCount = 0;
	int directLightsCount = 0;
	int pointLightsCount = 0;
	int spotLightsCount = 0;

	for (int i = 0; i < World::LightsOnScene.size(); i++) {

		ModulesList type = World::LightsOnScene[i]->GetType();

		if (type == ModulesList::DirectLightType) {
			auto light = (DirectLight*)(World::LightsOnScene[i]);
			directLightsCount++;

			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(i)).append("].direction"), &light->GetDirection());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(i)).append("].color"), &light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("directLights[").append(std::to_string(i)).append("].strength"), &light->strength);
			continue;
		}
		if (type == ModulesList::PointLightType) {
			auto light = (PointLight*)(World::LightsOnScene[i]);
			pointLightsCount++;

			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].position"), &light->GetPosition());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].color"), &light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].strength"), &light->strength);

			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].constant"), &light->constant);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].linear"), &light->linear);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("pointLights[").append(std::to_string(i)).append("].quadratic"), &light->quadratic);
			continue;

		}
		if (type == ModulesList::SpotLightType) {
			auto light = (SpotLight*)(World::LightsOnScene[i]);
			spotLightsCount++;

			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].direction"), &light->GetDirection());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].position"), &light->GetPosition());
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].color"), &light->color);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].strength"), &light->strength);

			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].cutOff"), &light->CutOff);
			ShaderProgram::SetValue(ShadersType::FragmentShader, std::string("spotLights[").append(std::to_string(i)).append("].outerCutOff"), &light->OuterCutOff);
			continue;

		}
	}

	directLightsCount = Math::Clamp(0, 16, directLightsCount);
	pointLightsCount = Math::Clamp(0, 16, pointLightsCount);
	spotLightsCount = Math::Clamp(0, 16, spotLightsCount);
	
	ShaderProgram::SetValue(ShadersType::FragmentShader, "ambientStrength", &World::WorldAmbientStrength);

	ShaderProgram::SetValue(ShadersType::FragmentShader, "DirectLightsCount", &directLightsCount);
	ShaderProgram::SetValue(ShadersType::FragmentShader, "PointLightsCount", &pointLightsCount);
	ShaderProgram::SetValue(ShadersType::FragmentShader, "SpotLightsCount", &spotLightsCount);


	ShaderProgram::SetValue(ShadersType::FragmentShader, "viewPos", &camera->GetPosition());
	
	glm::mat4x4 viewMat = camera->_projectionMatrix * camera->_transformMatrix;
	ShaderProgram::SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));

	ShaderProgram::ApplyShadersValue();
}

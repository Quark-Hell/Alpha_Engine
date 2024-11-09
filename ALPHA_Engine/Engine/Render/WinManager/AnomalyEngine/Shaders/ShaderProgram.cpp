#include "ShaderProgram.h"

#include <fstream>
#include <filesystem>
#include <iostream>

#include <GLEW/glew.h>

#include "Core/Math/Vectors.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"

namespace Render::AnomalyEngine::Shaders {

    ShaderProgram::ShaderProgram(Material* parentMat) {
    	if (parentMat == nullptr) {
    		std::cout << "Critical: parent material was null" << std::endl;
    		abort();
    	}

        _parentMaterial = parentMat;
    	std::cout << "Info: Base shader program created" << std::endl;
    }

    ShaderProgram::~ShaderProgram() {
        ShaderProgram::DeleteShader();

        if (_programId != 0)
            glDeleteProgram(_programId);

    	std::cout << "Info: Shader was be deleted" << std::endl;
    }

#pragma region Getter
    unsigned int ShaderProgram::GetVertexShaderId() const
    {
        return _vertexShaderId;
    }

    unsigned int ShaderProgram::GetTesselationControlShaderId() const
    {
        return _tessellationControlShaderId;
    }

    unsigned int ShaderProgram::GetTesselationEvaluationShaderId() const
    {
        return _tessellationEvaluationShaderId;
    }

    unsigned int ShaderProgram::GetGeometryShaderId() const
    {
        return _geometryShaderId;
    }

    unsigned int ShaderProgram::GetFragmentShaderId() const
    {
        return _fragmentShaderId;
    }

    unsigned int ShaderProgram::GetComputeShaderId() const
    {
        return _computeShaderId;
    }

    unsigned int ShaderProgram::GetProgramId() const
    {
        return _programId;
    }

    bool ShaderProgram::GetCompiledStatus() const
    {
        return _isCompiled;
    }

    Material* ShaderProgram::GetParentMaterial() const {
        return _parentMaterial;
    }

	RenderMode ShaderProgram::GetRenderMode() const {
	    return _renderMode;
    }
#pragma endregion

    bool ShaderProgram::BindShader() const {
        if (_isCompiled == false) {
        	std::cout << "Error: Shader was not be compiled" << std::endl;
        	return false;
        }


        if (_programId == 0) {
        	std::cout << "Error: Shader program was not be created on GPU" << std::endl;
        	return false;
        }

        glUseProgram(_programId);
        return true;
    }

    bool ShaderProgram::UnbindShader()
    {
        glUseProgram(0);
        return true;
    }

    bool ShaderProgram::AddShaderSource(const std::string& sourcePath, const ShadersType shaderType) {

		auto readShaderSource = [](const std::string& path, std::string& str) {

			const std::string genPath = std::filesystem::current_path().string() + path;
			std::cout << "Info: Read shader source by " << genPath << std::endl;
			std::ifstream sourceStream(genPath);
			if (sourceStream.is_open()) {
				str.clear();
				std::string line;
				while (std::getline(sourceStream, line)) {
					str += line + "\n";
				}

				sourceStream.close();
				return true;
			}
			std::cout << "Error: Could not read shader source by " << genPath << std::endl;
			return false;

		};

		const char* chSource;
    	const auto shaderSource = std::make_unique<std::string>();

		switch (shaderType)
		{
		case VertexShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_vertexShaderId, 1, &chSource, nullptr);
			break;

		case TessellationControlShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_tessellationControlShaderId = glCreateShader(GL_TESS_CONTROL_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_tessellationControlShaderId, 1, &chSource, nullptr);
			break;

		case TessellationEvaluationShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_tessellationEvaluationShaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_tessellationEvaluationShaderId, 1, &chSource, nullptr);
			break;

		case GeometryShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_geometryShaderId, 1, &chSource, nullptr);
			break;

		case FragmentShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_fragmentShaderId, 1, &chSource, nullptr);
			break;
		case ComputeShader:
			if (!readShaderSource(sourcePath, *shaderSource))
				return false;

			_computeShaderId = glCreateShader(GL_COMPUTE_SHADER);

			chSource = shaderSource->c_str();
			glShaderSource(_computeShaderId, 1, &chSource, nullptr);
			break;
		default:
			return false;
		}

		_isCompiled = false;
    	std::cout << "Info: Shader source was be moved to VRAM" << std::endl;
		return true;
    }

	bool ShaderProgram::CompileShader() {

    	auto TryCompile = [](const unsigned int shaderId, bool& compiledStatus) {
    		int success;

    		glCompileShader(shaderId);
    		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    		if (success == GL_FALSE)
    		{
    			char info_log[1024];
    			glGetShaderInfoLog(shaderId, 1024, nullptr, info_log);

    			std::cout << "Error: Shader compilation error: " << info_log;

    			compiledStatus = false;
    			return false;
    		}
    		std::cout << "Info: Shader was be compiled" << std::endl;
    		compiledStatus = true;
    		return true;
    	};

    	std::cout << "Info: Starting compiling shader" << std::endl;
    	if (_vertexShaderId != 0)
    		if (!(TryCompile(ShaderProgram::_vertexShaderId, ShaderProgram::_isCompiled)))
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

	bool ShaderProgram::AttachShader() {
    	if (ShaderProgram::_isCompiled == false) {
    		std::cout << "Error: Shader could not be attached because there was not be compiled. You need to use CompileShader() previously" << std::endl;
    		return false;
    	}

    	if (ShaderProgram::_programId == 0) {
    		ShaderProgram::_programId = glCreateProgram();
    		std::cout << "Info: New shader program was be created" << std::endl;
    	}

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

	//TODO: Maybe I need also detach shader
	void ShaderProgram::DeleteShader() const {
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

    	std::cout << "Info: Shader was be deleted from VRAM" << std::endl;
    }

	void ShaderProgram::ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) {

    }

	void ShaderProgram::SetRenderMode(const RenderMode mode) {
	    _renderMode = mode;
    }

	void ShaderProgram::SetValue(const UniformType type, const std::string& fieldName, void* value) const {
    	if (ShaderProgram::_programId == 0) {
    		std::cout << "Shader does not exist" << std::endl;
    		return;
    	}

    	if (type == UniformType::mat4x4) {
    		const auto* v = static_cast<glm::mat4x4*>(value);
    		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
    	}
    	else if (type == UniformType::mat3x3) {
    		const auto* v = static_cast<glm::mat3x3*>(value);
    		glUniformMatrix3fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
    	}
    	else if (type == UniformType::integer) {
    		const auto v = static_cast<int*>(value);
    		glUniform1i(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
    	}
    	else if (type == UniformType::unsigned_int) {
    		const auto* v = static_cast<unsigned int*>(value);
    		glUniform1ui(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
    	}
    	else if (type == UniformType::floatType) {
    		const auto* v = static_cast<float*>(value);
    		glUniform1f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
    	}
    	else if (type == UniformType::vec3) {
    		const auto* v = static_cast<Core::Vector3*>(value);
    		glUniform3f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), v->X, v->Y, v->Z);
    	}
    }
}
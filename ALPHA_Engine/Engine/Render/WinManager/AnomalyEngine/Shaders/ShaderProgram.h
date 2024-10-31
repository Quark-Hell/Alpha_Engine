#pragma once
#include <memory>
#include <string>

#include <GL/glew.h>

#include "Core/Math/Vectors.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include <iostream>

namespace Render::AnomalyEngine::Components {
	class Camera;
}

namespace Render::AnomalyEngine {
	class Material;
	class RenderEngine;
}

namespace Render::AnomalyEngine::Shaders {

    enum ShadersType  : unsigned short {
        VertexShader = 0,
        TessellationControlShader = 1,
        TessellationEvaluationShader = 2,
        GeometryShader = 3,
        FragmentShader = 4,
        ComputeShader = 5,
    };

class ShaderProgram {
	friend class Material;
	friend class Render::AnomalyEngine::RenderEngine;

private:
    unsigned int _vertexShaderId = 0;
    unsigned int _tessellationControlShaderId = 0;
    unsigned int _tessellationEvaluationShaderId = 0;
    unsigned int _geometryShaderId = 0;
    unsigned int _fragmentShaderId = 0;
    unsigned int _computeShaderId = 0;

    unsigned int _programId = 0;
    bool _isCompiled = false;

    Render::AnomalyEngine::Material* _parentMaterial;

public:
	ShaderProgram() = delete;
    virtual ~ShaderProgram();

    ShaderProgram& operator=(ShaderProgram&& shaderProgram);

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    #pragma region Interface
	[[nodiscard]] unsigned int GetVertexShaderId() const;
	[[nodiscard]] unsigned int GetTesselationControlShaderId() const;
	[[nodiscard]] unsigned int GetTesselationEvaluationShaderId() const;
	[[nodiscard]] unsigned int GetGeometryShaderId() const;
	[[nodiscard]] unsigned int GetFragmentShaderId() const;
	[[nodiscard]] unsigned int GetComputeShaderId() const;

	[[nodiscard]] unsigned int GetProgramId() const;
	[[nodiscard]] bool GetCompiledStatus() const;

	[[nodiscard]] Material* GetParentMaterial() const;

	template <typename T, typename = std::enable_if_t<
		std::is_same_v<glm::mat4x4, T> ||
		std::is_same_v<glm::mat3x3, T> ||
		std::is_same_v<int, T> ||
		std::is_same_v<unsigned int, T> ||
		std::is_same_v<float, T> ||
		std::is_same_v<Core::Vector3, T>
	>>
	void SetValue(const std::string& fieldName, T& value) {
		if (ShaderProgram::_programId == 0) {
			std::cout << "Shader does not exist" << std::endl;
			return;
		}

		if (std::is_same_v<glm::mat4x4, T>) {
			const auto* v = reinterpret_cast<glm::mat4x4*>(&value);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same_v<glm::mat3x3, T>) {
			const auto* v = reinterpret_cast<glm::mat3x3*>(&value);
			glUniformMatrix3fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*v));
		}
		else if (std::is_same_v<int, T>) {
			const auto v = reinterpret_cast<int*>(&value);
			glUniform1i(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same_v<unsigned int, T>) {
			const auto* v = reinterpret_cast<unsigned int*>(&value);
			glUniform1ui(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same_v<float, T>) {
			const auto* v = reinterpret_cast<float*>(&value);
			glUniform1f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *v);
		}
		else if (std::is_same_v<Core::Vector3, T>) {
			const auto* v = reinterpret_cast<Core::Vector3*>(&value);
			glUniform3f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), v->X, v->Y, v->Z);
		}
	}

#pragma endregion

	/**
     * Load shared source into VRAM.
    */
	bool AddShaderSource(const std::string& sourcePath, ShadersType shaderType);
	/**
	 * Compile shader.
	 *
	 * Shader source will be received from VRAM.
	 * Use AddShaderSource() to load shader source.
	*/
	bool CompileShader();

	/**
	 *Use this to create shader program after compiling shader.
	 *
	 *Previously shader program will be deleted from VRAM automatically.
	*/
	bool AttachShader();

	/**
     *Use this command for delete shader source from VRAM.
     *
     *NOTE: Always use this previously loading you shader to avoid leak memory.
     *This does not delete your shader program from VRAM
    */
	void DeleteShader() const;

protected:
	ShaderProgram(Material* parentMat);
	/** Sets the current shader for OpenGL
	*/
	bool BindShader() const;
	/** Sets the zero shader for OpenGL
	 *
	 * This means that current shader will be undefined
	*/
	bool UnbindShader();

	/*
	 *Overload this function to transfer your values from RAM to VRAM for shader
	*/
	virtual void ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) = 0;
};

}

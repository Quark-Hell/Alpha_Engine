#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Logger/Logger.h"

#include <memory>
#include <string>

namespace AnomalyEngine {
	class Camera;
	class Material;
	class RenderEngine;
}

template <typename T, typename... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

template<typename T>
concept UniformType =
std::is_arithmetic_v<T> ||
std::same_as<T, glm::vec2> ||
std::same_as<T, glm::vec3> ||
std::same_as<T, glm::vec4> ||
std::same_as<T, glm::mat3> ||
std::same_as<T, glm::mat4>;


namespace AnomalyEngine {
    enum ShadersType  : unsigned short {
        VertexShader = 0,
        TessellationControlShader = 1,
        TessellationEvaluationShader = 2,
        GeometryShader = 3,
        FragmentShader = 4,
        ComputeShader = 5,
    };

	enum class RenderMode : uint8_t {
		Points = 0,
		Lines = 1,
		LineStrip = 2,
		Triangles = 3,
	};

class ShaderProgram {
	friend class Material;
	friend class RenderEngine;

private:
    unsigned int _vertexShaderId = 0;
    unsigned int _tessellationControlShaderId = 0;
    unsigned int _tessellationEvaluationShaderId = 0;
    unsigned int _geometryShaderId = 0;
    unsigned int _fragmentShaderId = 0;
    unsigned int _computeShaderId = 0;

    unsigned int _programId = 0;
    bool _isCompiled = false;

    Material* _parentMaterial;

	RenderMode _renderMode = RenderMode::Triangles;
public:
	ShaderProgram() = delete;
    virtual ~ShaderProgram();

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

	[[nodiscard]] RenderMode GetRenderMode() const;


    template<UniformType T>
	void SetValue(const std::string& fieldName, T* value) const{
        if (ShaderProgram::_programId == 0) {
            Core::Logger::LogInfo("Shader does not exist");
            return;
        }

        if constexpr (std::is_same_v<glm::mat4x4, T> == true){
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*value));
        }
        else if constexpr (std::is_same_v<glm::mat3x3, T> == true){
            glUniformMatrix3fv(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), 1, GL_FALSE, glm::value_ptr(*value));
        }
        else if constexpr (std::is_same_v<float, T> == true){
            glUniform1f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *value);
        }
        else if constexpr (std::is_same_v<int, T> == true){
            glUniform1i(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *value);
        }
        else if constexpr (std::is_same_v<unsigned int, T> == true){
            glUniform1ui(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), *value);
        }

        else if constexpr (std::is_same_v<glm::vec3, T> == true){
            glUniform3f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), value->x, value->y, value->z);
        }
        else if constexpr (std::is_same_v<glm::vec2, T> == true){
            glUniform2f(glGetUniformLocation(ShaderProgram::_programId, fieldName.c_str()), value->x, value->y);
        }
    }

	void SetRenderMode(RenderMode mode);

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
	virtual void ApplyShadersSettings(Camera& camera) = 0;
};

}

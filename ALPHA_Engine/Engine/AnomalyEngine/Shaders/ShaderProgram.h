#pragma once
#include <memory>
#include <string>

namespace AnomalyEngine {
	class Camera;
	class Material;
	class RenderEngine;
}

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

	enum class UniformType : uint8_t {
		mat4x4 = 0,
		mat3x3 = 1,
		integer = 2,
		unsigned_int = 3,
		floatType = 4,
		vec3 = 5,
	};
	void SetValue(UniformType type, const std::string& fieldName, void* value) const;

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

#pragma once
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShadersProgram/ShaderProgram.h"
#include "Modules/Mesh.h"

enum ShadersType;

namespace GraphicsEngine {

	class Material
	{
	private:
		Mesh* _parentMesh;

	public:
		std::shared_ptr<ShaderProgram> Shader;

	public:
		Material();
		~Material();

		bool InitShader();

		Mesh* GetParentMesh();

	protected:
		friend class RenderCore;
		friend class Mesh;
		friend class ShaderProgram;
	};

}

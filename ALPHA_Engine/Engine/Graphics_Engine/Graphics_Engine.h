#pragma once
class Camera;

enum RenderModes : unsigned short;

#include "BaseConfig.h"
#include "Graphics_Engine/Modules/Screen.h"

namespace Core {
	class Host;
}

namespace GraphicsEngine {
	class RenderCore {
		friend class Core::Host;

	private:
		Screen _screenClass;
		//std::vector<std::unique_ptr<Camera>>* _cameras;

	private:
		static std::unique_ptr<GraphicsEngine::RenderCore> MakeRenderCore();
		RenderCore();

		void PrepareToRender();
		void ClearFrameBuffer();

	public:
		~RenderCore();

		void StartRender();
		void RenderLoop();
		Screen* GetScreenClass();

		bool CompileShaders();

	private:
		void SceneAssembler(std::shared_ptr<Camera> camera);

		void SetMeshRenderOptions();


		//void RenderMesh(Mesh& mesh, std::shared_ptr<Camera>  camera);

		int GetRenderMode(RenderModes renderMode);

		void ApplyCameraTransform(std::shared_ptr<Camera>  camera);
	};
}
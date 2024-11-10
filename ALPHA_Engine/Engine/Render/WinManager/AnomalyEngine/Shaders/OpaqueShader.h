#pragma once

#include "ShaderProgram.h"
#include "Render/WinManager/AnomalyEngine/Textures/OpenGLTexture.h"

namespace Render::AnomalyEngine::Shaders {

class OpaqueShader final : public ShaderProgram {

private:
  Textures::OpenGLTexture _diffuse;
  Textures::OpenGLTexture _metallic;
  Textures::OpenGLTexture _specular;
  Textures::OpenGLTexture _roughness;
  Textures::OpenGLTexture _anisotropic;
  Textures::OpenGLTexture _emission;
  Textures::OpenGLTexture _normalsMap;
  Textures::OpenGLTexture _opacityMap;
  Textures::OpenGLTexture _occlusionMap;

public:
  OpaqueShader(Material* parentMat);
  ~OpaqueShader() override = default;

  void LoadTextures(
      const std::string& diffusePath,
      const std::string& metallicPath,
      const std::string& specularPath,
      const std::string& roughnessPath,
      const std::string& anisotropicPath,
      const std::string& emissionPath,
      const std::string& normalsMapPath,
      const std::string& opacityMapPath,
      const std::string& occlusionMapPath
  );


  void ApplyShadersSettings(Render::AnomalyEngine::Components::Camera* camera) override;
};

}

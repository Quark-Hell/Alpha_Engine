#pragma once

namespace Render::AnomalyEngine::Components {
    class Mesh;
}

namespace Render::AnomalyEngine {

class Binder {
    private:
      Binder() = default;

    public:
      ~Binder() = default;

      static bool BindMesh(Components::Mesh* mesh);
      static bool BindImage();
      //static bool Bind...
};

}
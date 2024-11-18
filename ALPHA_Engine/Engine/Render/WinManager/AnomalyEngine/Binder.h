#pragma once

namespace Render::WindowsManager {
    class Window;
    namespace AnomalyEngine {
        class Mesh;
    }
}

namespace Render::WindowsManager::AnomalyEngine {

class Binder {
    private:
      Binder() = default;

    public:
      ~Binder() = default;

      static bool BindMesh(Mesh* mesh);
      static bool BindImage();
      //static bool SharedBindMesh(Components::Mesh* mesh);
      //static bool Bind...
};

}
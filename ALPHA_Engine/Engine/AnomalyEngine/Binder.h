#pragma once

namespace AnomalyEngine {
    class Mesh;

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
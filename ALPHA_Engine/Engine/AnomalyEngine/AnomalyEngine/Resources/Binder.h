#pragma once

namespace AnomalyEngine {
    class Mesh;

    class Binder {
        friend class Mesh;

    private:
        unsigned int _vertexVbo = 0;
        unsigned int _colorsVbo = 0;
        unsigned int _normalsVbo = 0;
        unsigned int _texCoordsVbo = 0;

    public:
        Binder() = default;
        ~Binder() = default;

        bool BindMesh(const Mesh& mesh);
        //static bool SharedBindMesh(Components::Mesh* mesh);
    };

}
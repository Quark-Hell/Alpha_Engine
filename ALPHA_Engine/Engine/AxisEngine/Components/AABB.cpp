#include "AABB.h"

#include "Core/Logger/Logger.h"

#if _DEBUG && ANOMALY_ENGINE_INCLUDED
#include "Core/World.h"
#include "Core/Factory.h"

#include "AnomalyEngine/Buffers/MeshesBuffer.h"
#include "AnomalyEngine/Components/Mesh.h"

#include "AnomalyEngine/Components/Material.h"
#include "AnomalyEngine/Shaders/OpaqueShader.h"
#endif // _DEBUG

namespace AxisEngine {
#if _DEBUG && ANOMALY_ENGINE_INCLUDED
    AABB::AABB() :_fakeObject(Core::Factory::CreateFakeObject()) {
        auto* buffer = Core::World::GetSystemData("MeshBuffer");

        if (buffer == nullptr) {
            Core::Logger::LogError("Meshes buffer not found: " + __LOGERROR__);
        }
        else {
            AnomalyEngine::MeshesBuffer* meshesBuffer = reinterpret_cast<AnomalyEngine::MeshesBuffer*>(buffer);
            _mesh = &meshesBuffer->CreateMesh();
            _fakeObject.AddComponent(*_mesh);

            _mesh->_material.InitShader<AnomalyEngine::OpaqueShader>();
        }

        AABB::CreateAABB();

        Core::Logger::LogInfo("AABB was created");
    }
#else
    AABB::AABB() {
        AABB::CreateAABB();

        Core::Logger::LogInfo("AABB was created");
    }
#endif // _DEBUG

#ifdef _DEBUG
    void AABB::CreateAABB() {
        auto pushVertex = [&](float x, float y, float z)
            {
                _vertices->push_back(x);
                _vertices->push_back(y);
                _vertices->push_back(z);
            };

        pushVertex(-1, -1, 1);
        pushVertex(-1, 1, 1);

        pushVertex(-1, 1, 1);
        pushVertex(1, 1, 1);

        pushVertex(1, 1, 1);
        pushVertex(1, -1, 1);

        pushVertex(1, -1, 1);
        pushVertex(-1, -1, 1);

        pushVertex(-1, -1, 1);
        pushVertex(-1, -1, -1);

        pushVertex(-1, -1, -1);
        pushVertex(-1, 1, -1);

        pushVertex(-1, 1, -1);
        pushVertex(-1, 1, 1);

        pushVertex(-1, 1, -1);
        pushVertex(1, 1, -1);

        pushVertex(1, 1, -1);
        pushVertex(1, -1, -1);

        pushVertex(1, -1, -1);
        pushVertex(-1, -1, -1);

        pushVertex(1, -1, -1);
        pushVertex(1, -1, 1);

        pushVertex(1, 1, -1);
        pushVertex(1, 1, 1);
    }
#endif // _DEBUG

}
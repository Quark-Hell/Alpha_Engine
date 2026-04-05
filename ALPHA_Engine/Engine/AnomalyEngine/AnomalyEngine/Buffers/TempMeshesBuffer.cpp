#include "TempMeshesBuffer.h"

#include "Core/Objects/FakeObject.h"
#include "Core/World.h"

namespace AnomalyEngine {
    TempMeshesBuffer::TempMeshesBuffer(size_t initialBufferSize) : TSystemData("TempMeshesBuffer", initialBufferSize) {}

    void TempMeshesBuffer::RemoveObjectsBuffer() {

        for (auto obj : _attachedObjects) {
            Core::World::DeleteObject(*obj);
        }

        _attachedObjects.clear();
    }
}

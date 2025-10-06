#include "RigidBodiesBuffer.h"

namespace AxisEngine {
    RigidBodiesBuffer::RigidBodiesBuffer(size_t initialBufferSize) : TSystemData("RigidBodiesBuffer", initialBufferSize) {}

    RigidBody& RigidBodiesBuffer::CreateRigidBody() {
        _data.emplace_back(std::unique_ptr<RigidBody>(new RigidBody()));

        return *_data.back().get();
    }
}
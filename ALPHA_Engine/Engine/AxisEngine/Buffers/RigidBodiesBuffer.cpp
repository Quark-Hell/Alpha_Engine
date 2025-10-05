#include "RigidBodiesBuffer.h"

namespace AxisEngine {
    RigidBodiesBuffer::RigidBodiesBuffer() : TSystemData("RigidBodiesBuffer") {
        _data.reserve(16);
    }

    RigidBody& RigidBodiesBuffer::CreateRigidBody() {
        _data.emplace_back(std::unique_ptr<RigidBody>(new RigidBody()));

        return *_data.back().get();
    }
}
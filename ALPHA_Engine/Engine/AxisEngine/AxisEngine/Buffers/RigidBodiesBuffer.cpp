#include "RigidBodiesBuffer.h"

namespace AxisEngine {
    RigidBodiesBuffer::RigidBodiesBuffer(size_t initialBufferSize) : TSystemData("RigidBodiesBuffer", initialBufferSize) {}

    RigidBody& RigidBodiesBuffer::CreateRigidBody(PhysicsEngine& engine, AxisEngine::RigidBodyType rigidBodyType) {
        _data.emplace_back(std::unique_ptr<RigidBody>(new RigidBody(engine, rigidBodyType)));

        return *_data.back().get();
    }
}
#include "ConvexMeshCollider.h"

#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Core/Resources/Geometry.h"
#include "Core/Objects/Object.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Components/Rigidbody.h"

#include "AxisEngine/External/PhysX/PxPhysicsAPI.h"

namespace AxisEngine {
    ConvexMeshCollider::ConvexMeshCollider(PhysicsEngine& engine) : Collider::Collider(engine) {
        ResetShape();
    }

    void ConvexMeshCollider::OnParentObjectChanged(Core::Object& newParent) {
        {
            if (auto oldParent = GetParentObject()) {
                if (auto oldRb = oldParent->GetComponentByType<AxisEngine::RigidBody>()) {
                    if (auto actor = oldRb->GetRigidActor()) {
                        actor->detachShape(*_shape.get());
                        _shape->release();
                    }
                }
            }
        }

        auto rb = newParent.GetComponentByType<AxisEngine::RigidBody>();

        if (rb != nullptr) {
            auto actor = rb->GetRigidActor();
            if (actor != nullptr) {
                UpdateScale();
                actor->attachShape(*_shape);
            }
        }
    }

    void ConvexMeshCollider::LoadGeometry(Core::Geometry& geometry) {
        std::vector<physx::PxVec3> physxVertices;

        physxVertices.reserve(geometry.Vertices->size() / 3);

        for (size_t i = 0; i < geometry.Vertices->size(); i += 3) {
            physxVertices.push_back(
                physx::PxVec3(
                    geometry.Vertices->at(i),
                    geometry.Vertices->at(i + 1),
                    geometry.Vertices->at(i + 2)
                )
            );
        }

        physx::PxCookingParams params(_physics->getTolerancesScale());
        params.convexMeshCookingType = physx::PxConvexMeshCookingType::eQUICKHULL;
        params.gaussMapLimit = 256; // опционально, улучшает качество коллизий

        physx::PxConvexMeshDesc desc;
        desc.points.count = physxVertices.size();
        desc.points.stride = sizeof(physx::PxVec3);
        desc.points.data = physxVertices.data();
        desc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;
                
        physx::PxDefaultMemoryOutputStream buf;
        physx::PxConvexMeshCookingResult::Enum result;

        bool ok = PxCookConvexMesh(params, desc, buf, &result);

        if (!ok)
        {
            Core::Logger::LogCritical("Cannot cook convex mesh. Error: " + result, __LOGERROR__);
            return;
        }
        
        physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
        _convexMesh.reset(_physics->createConvexMesh(input));

        if (!_convexMesh)
        {
            Core::Logger::LogCritical("ConvexMesh is null", __LOGERROR__);
            return;
        }

        if (_parentObject == nullptr) {
            ResetShape();
        }
        else
        {
            UpdateScale();
        }
    }

    void ConvexMeshCollider::ResetShape() {
        //if (_convexMesh == nullptr) {
        //    Core::Logger::LogError("Cannot reset shape. Convex mesh is null", __LOGERROR__);
        //    return;
        //}
        //
        if (_material == nullptr) {
            Core::Logger::LogError("Cannot reset shape. Material is null", __LOGERROR__);
            return;
        }

        physx::PxMeshScale meshScale(_scale, physx::PxQuat(physx::PxIdentity));
        physx::PxConvexMeshGeometry geom(_convexMesh.get(), meshScale);

        if (_shape) {
            _shape->setGeometry(geom);
        }
        else {
            _shape.reset(_physics->createShape(geom, *_material, true));
        }
    }
}
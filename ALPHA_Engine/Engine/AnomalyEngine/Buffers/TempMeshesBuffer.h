#pragma once

#include "AnomalyEngine/Utility/BasicShapes/Shape.h"

#include "Core/ECS/TSystemData.h"
#include "Core/Objects/FakeObject.h"
#include "Core/Factory.h"

namespace AnomalyEngine {
    class TempMeshesBuffer final : public Core::TSystemData<Shape> {
        friend class RenderEngine;

    private:
        std::vector<Core::FakeObject*> _attachedObjects;

    private:
        template <DerivedShape T>
        Shape& CreateMesh() {
            _data.emplace_back(std::unique_ptr<T>(new T()));
            _data.back().get()->Create();

            return *_data.back().get();
        }

        void RemoveObjectsBuffer();

    public:
        TempMeshesBuffer(size_t initialBufferSize = 0);
        ~TempMeshesBuffer() override = default;

        template <DerivedShape T>
        void Draw(glm::vec3 position, glm::vec3 rotation = glm::vec3{0,0,0}, glm::vec3 scale = glm::vec3{ 1,1,1 }) {
            Core::FakeObject& obj = Core::Factory::CreateFakeObject();

            obj.transform.SetPosition(position);
            obj.transform.SetRotation(rotation);
            obj.transform.SetScale(scale);

            for (auto& it : _data) {
                if (auto* shape = dynamic_cast<T*>(it.get())) {
                    obj.AddComponent(*shape);
                    break;
                }
            }

            _attachedObjects.push_back(&obj);
        }
    };
}


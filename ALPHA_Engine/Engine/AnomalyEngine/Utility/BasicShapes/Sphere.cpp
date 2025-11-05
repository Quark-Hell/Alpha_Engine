#include "Sphere.h"

#include "AnomalyEngine/Resources/Binder.h"

namespace AnomalyEngine {
    Sphere::Sphere(Color shapeColor) : Shape(shapeColor) {

	}

    bool Sphere::Create() {
        constexpr float radius = 1;

        glm::vec3 c = glm::vec3(ShapeColor.r, ShapeColor.g, ShapeColor.b);
        std::array<glm::vec3, 6> points;

        _geometry->Vertices->clear();
        _geometry->VertexColors->clear();

        for (size_t i = 0; i < _segments; ++i)
        {
            float theta1 = glm::radians((float)i / _segments * 360.0f);
            float theta2 = glm::radians((float)(i + 1) / _segments * 360.0f);

            points[0] = glm::vec3(radius * cos(theta1), 0, radius * sin(theta1));
            points[1] = glm::vec3(radius * cos(theta2), 0, radius * sin(theta2));

            points[2] = glm::vec3(0, radius * cos(theta1), radius * sin(theta1));
            points[3] = glm::vec3(0, radius * cos(theta2), radius * sin(theta2));

            points[4] = glm::vec3(radius * cos(theta1), radius * sin(theta1), 0);
            points[5] = glm::vec3(radius * cos(theta2), radius * sin(theta2), 0);

            // 3 great circles
            for (size_t j = 0; j < points.size(); j++) {
                _geometry->Vertices->push_back(points[j].x);
                _geometry->Vertices->push_back(points[j].y);
                _geometry->Vertices->push_back(points[j].z);
            }

            for (size_t j = 0; j < 6; j++) {
                _geometry->VertexColors->push_back(c.x);
                _geometry->VertexColors->push_back(c.y);
                _geometry->VertexColors->push_back(c.z);
            }
        }

        _geometry->IsIndexed = false;
        Core::Logger::LogInfo("Mesh has been loaded");

        if (_binder == nullptr) {
            _binder = std::make_shared<AnomalyEngine::Binder>();
        }
        _binder->BindMesh(*this);

        return true;
    }
}
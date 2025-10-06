#pragma once

#include <array>
#include "Core/Math/glmMath.h"

namespace AxisEngine {
	class Simplex {
    private:
        std::array<glm::vec3, 4> _points;
        unsigned _size;

    public:
        Simplex(std::array<glm::vec3, 4> points, unsigned size);
        void PushFront(glm::vec3 point);
        unsigned GetSize();

        bool NextSimplex(Simplex& points, glm::vec3& direction);
        bool SameDirection(glm::vec3 direction, glm::vec3 ao);

        bool Line(Simplex& points, glm::vec3& direction);
        bool Triangle(Simplex& points, glm::vec3& direction);
        bool Tetrahedron(Simplex& points, glm::vec3& direction);

        Simplex& operator=(std::initializer_list < glm::vec3> list) {
            for (auto v = list.begin(); v != list.end(); v++) {
                Simplex::_points[std::distance(list.begin(), v)] = *v;
            }
            Simplex::_size = list.size();

            return *this;
        }

        glm::vec3& operator[](unsigned i) { return Simplex::_points[i]; }

        auto begin() const { return Simplex::_points.begin(); }
        auto end()   const { return Simplex::_points.end() - (4 - Simplex::_size); }
	};
}

#include "Simplex.h"

#include <algorithm>

namespace AxisEngine {
    Simplex::Simplex(std::array<glm::vec3, 4> points, unsigned size) {
        Simplex::_points = points;
        Simplex::_size = size;
    }
    void Simplex::PushFront(glm::vec3 point) {
        _points = { point, _points[0], _points[1], _points[2] };
        _size = std::min(_size + 1, 4u);
    }
    unsigned Simplex::GetSize() {
        return _size;
    }

    bool Simplex::NextSimplex(Simplex& points, glm::vec3& direction) {
        switch (points.GetSize()) {
        case 2: return Line(points, direction);
        case 3: return Triangle(points, direction);
        case 4: return Tetrahedron(points, direction);
        }

        // never should be here
        return false;
    }
    bool Simplex::SameDirection(glm::vec3 direction, glm::vec3 ao) {
        return glm::dot(direction, ao) > 0;
    }

    bool Simplex::Line(Simplex& points, glm::vec3& direction) {
        glm::vec3 a = points[0];
        glm::vec3 b = points[1];

        glm::vec3 ab = b - a;
        glm::vec3 ao = -a;

        if (SameDirection(ab, ao)) {
            direction = glm::cross(glm::cross(ab, ao), ab);
        }

        else {
            points = { a };
            direction = ao;
        }

        return false;
    }
    bool Simplex::Triangle(Simplex& points, glm::vec3& direction) {
        glm::vec3 a = points[0];
        glm::vec3 b = points[1];
        glm::vec3 c = points[2];

        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 ao = -a;

        glm::vec3 abc = glm::cross(ab, ac);

        if (SameDirection(glm::cross(abc,ac), ao)) {
            if (SameDirection(ac, ao)) {
                points = { a, c };
                direction = glm::cross(glm::cross(ac, ao), ac);
            }

            else {
                return Line(points = { a, b }, direction);
            }
        }

        else {
            if (SameDirection(glm::cross(ab, abc), ao)) {
                return Line(points = { a, b }, direction);
            }

            else {
                if (SameDirection(abc, ao)) {
                    direction = abc;
                }

                else {
                    points = { a, c, b };
                    direction = -abc;
                }
            }
        }

        return false;
    }

    bool Simplex::Tetrahedron(Simplex& points, glm::vec3& direction) {
        glm::vec3 a = points[0];
        glm::vec3 b = points[1];
        glm::vec3 c = points[2];
        glm::vec3 d = points[3];

        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 ad = d - a;
        glm::vec3 ao = -a;

        glm::vec3 abc = glm::cross(ab, ac);
        glm::vec3 acd = glm::cross(ac, ad);
        glm::vec3 adb = glm::cross(ad, ab);

        if (SameDirection(abc, ao)) {
            return Triangle(points = { a, b, c }, direction);
        }

        if (SameDirection(acd, ao)) {
            return Triangle(points = { a, c, d }, direction);
        }

        if (SameDirection(adb, ao)) {
            return Triangle(points = { a, d, b }, direction);
        }

        return true;
    }

}
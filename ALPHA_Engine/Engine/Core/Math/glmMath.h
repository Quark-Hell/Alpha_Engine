#pragma once

#include <algorithm>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/intersect.hpp>

#include <glm/gtc/constants.hpp>

namespace glm {
    template<typename T, typename... U>
    concept IsAnyOf = (std::same_as<T, U> || ...);

    template<typename T>
    concept glmVector = IsAnyOf<T, glm::vec2, glm::vec3, glm::vec4>;

    template<glmVector T>
    [[nodiscard]] static inline constexpr bool InSegment(T point, T startSegment, T endSegment){
        if (point.x < std::min(startSegment.x, endSegment.x) || point.x > std::max(startSegment.x, endSegment.x)) {
            return false;
        }
        if (point.y < std::min(startSegment.y, endSegment.y) || point.y > std::max(startSegment.y, endSegment.y)) {
            return false;
        }

        return true;
    }

    template<glmVector T>
    [[nodiscard]] static inline constexpr T GetRectangleCenter(
            T left,
            T right,
            T top,
            T bottom) {

        T center = (left + right + top + bottom) / 4.0f;
        return center;
    }

    template<glmVector T>
    [[nodiscard]] static inline bool CheckAABBIntersection(
            const T& leftCorner1,
            const T& rightCorner1,
            const T& leftCorner2,
            const T& rightCorner2) {

        if (rightCorner1.x < leftCorner2.x || rightCorner2.x < leftCorner1.x) {
            return false;
        }
        if (rightCorner1.y < leftCorner2.y || rightCorner2.y < leftCorner1.y) {
            return false;
        }

        if constexpr (std::is_same_v<T, glm::vec3>){
            if (rightCorner1.z < leftCorner2.z || rightCorner2.z < leftCorner1.z) {
                return false;
            }
        }
        if constexpr (std::is_same_v<T, glm::vec4>){
            if (rightCorner1.z < leftCorner2.z || rightCorner2.z < leftCorner1.z) {
                return false;
            }
            if (rightCorner1.w < leftCorner2.w || rightCorner2.w < leftCorner1.w) {
                return false;
            }
        }

        return true;
    }

    template<glmVector T>
    [[nodiscard]] static inline T ProjectPointOnAxis(T point, T axisP1, T axisP2) {
        T axisVector = glm::normalize(axisP2 - axisP1);
        T pointVector = point - axisP1;

        float projection;

        if constexpr (std::is_same_v<T, glm::vec2>) {
            projection =
                    axisVector.x * pointVector.x +
                    axisVector.y * pointVector.y;
        }
        else if constexpr (std::is_same_v<T, glm::vec3>) {
            projection =
                    axisVector.x * pointVector.x +
                    axisVector.y * pointVector.y +
                    axisVector.z * pointVector.z;
        }
        else if constexpr (std::is_same_v<T, glm::vec4>) {
            projection =
                    axisVector.x * pointVector.x +
                    axisVector.y * pointVector.y +
                    axisVector.z * pointVector.z +
                    axisVector.w * pointVector.w;
        }

        T projectPoint{axisP1 + axisVector * projection};
        return projectPoint;
    }

    //TODO:: it doesn't work
    template<glmVector T>
    [[nodiscard]] static inline float DistanceBetweenAxis(std::pair<T, T> axis1, std::pair<T, T> axis2) {
        T vec1 = axis1.second - axis1.first;
        T vec2 = axis2.second - axis2.first;

        T delta = vec1 - vec2;

        float distance = glm::length(delta);

        return distance;
    }

    template<glmVector T>
    [[nodiscard]] static inline bool ClosetPointBetweenAxis(std::pair<T, T> axis1,std::pair<T, T> axis2, T& point) {
        T axis1Vector = glm::normalize(axis1.second - axis1.first);
        T axis2Vector = glm::normalize(axis2.second - axis2.first);

        float normU = glm::dot(axis1Vector, axis2Vector);

        //parallel
        if (std::fabs(normU) == 1)
            return false;

        T cn = glm::normalize(glm::cross(axis2Vector ,axis1Vector));
        T rejection = axis2.first - axis1.first - axis1Vector * glm::dot(axis2.first - axis1.first, axis1Vector) - cn * glm::dot(axis2.first - axis1.first, cn);
        T closetApproach = axis2.first - axis2Vector * glm::length(rejection) / glm::dot(axis2Vector, glm::normalize(rejection));

        point = closetApproach;
        return true;
    }
}



//namespace Core{
//
//        static inline bool LineToPlaneIntersection(std::pair<Vector3, Vector3> line,
//                                                   Vector3 pA, Vector3 pB, Vector3 pC,
//                                                   Vector3& intersectPoint) {
//
//            line.first.NormilizeSelf();
//            line.second.NormilizeSelf();
//
//            Vector3 lineVector = line.second - line.first;
//
//            Vector3 planeVectorA = pB - pA;
//            Vector3 planeVectorB = pC - pA;
//
//            Vector3 planeNorm = Vector3::GetNormalize(Vector3::CrossProduct(planeVectorA, planeVectorB));
//
//            float u = Vector3::DotProduct(planeNorm, lineVector);
//
//            //has not contact
//            if (fabs(u) < 0.001f)
//                return false;
//
//            float t = ((pA.X - line.first.X) * planeNorm.X + (pA.Y - line.first.Y) * planeNorm.Y + (pA.Z - line.first.Z) * planeNorm.Z) /
//                      (planeNorm.X * (lineVector.X) + planeNorm.Y * (lineVector.Y) + planeNorm.Z * (lineVector.Z));
//
//            intersectPoint = line.first + (lineVector * t);
//            return true;
//        }
//
//        static inline float GetVertexToPlaneDistance(Vector3 vertex, Vector3 p1, Vector3 normal) {
//            normal.NormilizeSelf();
//
//            float numerator = std::abs(
//                    (vertex.X - p1.X) * normal.X +
//                    (vertex.Y - p1.Y) * normal.Y +
//                    (vertex.Z - p1.Z) * normal.Z);
//
//            float denominator = std::sqrt(
//                    normal.X * normal.X +
//                    normal.Y * normal.Y +
//                    normal.Z * normal.Z);
//
//            return numerator / denominator;
//        }
//
//}
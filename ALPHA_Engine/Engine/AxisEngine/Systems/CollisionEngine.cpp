#include "CollisionEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Buffers/CollidersBuffer.h"
#include "AxisEngine/Buffers/RigidBodiesBuffer.h"

#include "AnomalyEngine/Utility/BasicShapes/Sphere.h"
#include "AnomalyEngine/Buffers/TempMeshesBuffer.h"

namespace AxisEngine {
    CollisionEngine::CollisionEngine(size_t order) : System({ "CollidersBuffer", "RigidBodiesBuffer" }, order) {}

    void CollisionEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
        if (data[0] == nullptr || data[1] == nullptr) {
            Core::Logger::LogError("Data was null: " + __LOGERROR__);
            return;
        }

        auto* collidersBuffer = reinterpret_cast<CollidersBuffer*>(data[0]);
        auto* rigidBodiesBuffer = reinterpret_cast<RigidBodiesBuffer*>(data[1]);

        //Clear collision Info
        for (auto& rigidBody : rigidBodiesBuffer->_data) {
            if (rigidBody != nullptr) {
                rigidBody->ClearCollisinInfo();
            }
        }

        //Check collision
        for (auto& colliderA : collidersBuffer->_data) {
            if (colliderA == nullptr)
                continue;

            Core::Object* objA = colliderA->GetParentObject();

            if (objA == nullptr)
                continue;

            for (auto& colliderB : collidersBuffer->_data) {
                if (colliderB == nullptr)
                    continue;

                Core::Object* objB = colliderB->GetParentObject();

                if (objB == nullptr)
                    continue;

                if (objA == objB)
                    continue;

                if (colliderA == colliderB)
                    continue;

                CollisionEngine::GJK(*colliderA, *colliderB);
            }
        }
    }

    glm::vec3 CollisionEngine::Support(Collider& colliderA, Collider& colliderB, glm::vec3 direction)
    {
        // Get transform matrices
        glm::mat4 transformA = colliderA.GetParentObject()->transform.GetTransformMatrix();
        glm::mat4 transformB = colliderB.GetParentObject()->transform.GetTransformMatrix();

        // Converting directions into local spaces
        glm::vec3 localDirA = glm::mat3(glm::inverse(transformA)) * direction;
        glm::vec3 localDirB = glm::mat3(glm::inverse(transformB)) * -direction;

        // Normalize directions after transformation
        localDirA = glm::normalize(localDirA);
        localDirB = glm::normalize(localDirB);

        // Finding points in local spaces
        glm::vec3 pointA_local = colliderA.FindFurthestPoint(localDirA);
        glm::vec3 pointB_local = colliderB.FindFurthestPoint(localDirB);

        // Convert to world spaces
        glm::vec3 pointA_world = glm::vec3(transformA * glm::vec4(pointA_local, 1.0f));
        glm::vec3 pointB_world = glm::vec3(transformB * glm::vec4(pointB_local, 1.0f));

        return pointA_world - pointB_world;
    }


    bool CollisionEngine::GJK(Collider& colliderA, Collider& colliderB) {
        CollisionInfo colInfo;

        // Get initial support point in any direction
        glm::vec3 support = Support(colliderA, colliderB, { 1,0,0 });

        // Simplex is an array of points, max count is 4
        Simplex points;
        points.PushFront(support);

        // New direction is towards the origin
        glm::vec3 direction = -support;

        for (unsigned int i = 0; i < CollisionEngine::GJKaccurate; i++) {
            support = Support(colliderA, colliderB, direction);

            if (support == glm::vec3(0,0,0)) {
                Core::Logger::LogError("Support was zero:" + __LOGERROR__);
                return false;
            }

            if (glm::dot(support, direction) < 0) {
                return false; // no collision
            }

            points.PushFront(support);

            if (Simplex::NextSimplex(points, direction)) {
                auto rb1 = colliderA.GetParentObject()->GetComponentByType<RigidBody>();
                auto rb2 = colliderB.GetParentObject()->GetComponentByType<RigidBody>();

                if (rb1 != nullptr && rb2 == nullptr) {
                    if (CollisionEngine::EPA(points, colliderA, colliderB, colInfo)) {
                        rb1->_pullingVectors.push_back(-colInfo.Normal * colInfo.PenetrationDepth);

                        colliderA.GetParentObject()->transform.AddPosition(-colInfo.Normal * colInfo.PenetrationDepth);
                        CollisionEngine::CalculateContactPoints(colliderA, colliderB, colInfo);

                        rb1->AddContactPoints(colInfo.CollisionPoints);
                        rb1->_hasCollision = true;

                        RigidBody::Contact(*rb1, -colInfo.Normal);

                        return true;
                    }
                }
                else if (rb1 == nullptr && rb2 != nullptr) {
                    if (CollisionEngine::EPA(points, colliderA, colliderB, colInfo)) {
                        rb2->_pullingVectors.push_back(colInfo.Normal * colInfo.PenetrationDepth);

                        colliderB.GetParentObject()->transform.AddPosition(colInfo.Normal * colInfo.PenetrationDepth);
                        CollisionEngine::CalculateContactPoints(colliderA, colliderB, colInfo);

                        rb2->AddContactPoints(colInfo.CollisionPoints);
                        rb2->_hasCollision = true;

                        RigidBody::Contact(*rb2, colInfo.Normal);

                        return true;
                    }


                }
                else if (rb1 != nullptr && rb2 != nullptr) {
                    if (CollisionEngine::EPA(points, colliderB, colliderA, colInfo)) {
                        glm::vec3 nowPos = colliderA.GetParentObject()->transform.GetPosition();

                        rb1->_pullingVectors.push_back(-colInfo.Normal * colInfo.PenetrationDepth * 0.5f);
                        rb2->_pullingVectors.push_back(colInfo.Normal * colInfo.PenetrationDepth * 0.5f);

                        colliderA.GetParentObject()->transform.AddPosition(colInfo.Normal * colInfo.PenetrationDepth);
                        CollisionEngine::CalculateContactPoints(colliderB, colliderA, colInfo);

                        rb1->AddContactPoints(colInfo.CollisionPoints);
                        rb2->AddContactPoints(colInfo.CollisionPoints);

                        rb1->_hasCollision = true;
                        rb2->_hasCollision = true;

                        colliderA.GetParentObject()->transform.SetPosition(nowPos);
                        RigidBody::Contact(*rb1, *rb2, -colInfo.Normal);

                        return true;
                    }


                }
                return true;
            }
        }
        return false;
    }
    bool CollisionEngine::EPA(Simplex& simplex, Collider& colliderA, Collider& colliderB, CollisionInfo& colInfo)
    {
        std::vector<glm::vec3> polytope(simplex.begin(), simplex.end());
        std::vector<size_t>  faces = {
            0, 1, 2,
            0, 3, 1,
            0, 2, 3,
            1, 3, 2
        };

        // list: vector4(normal, distance), index: min distance
        auto [normals, minFace] = GetFaceNormals(polytope, faces);

        glm::vec3 minNormal;
        float   minDistance = FLT_MAX;

        for (unsigned int i = 0; i < CollisionEngine::EPAaccurate; i++) {
            if (minDistance == FLT_MAX) {
                minNormal = normals[minFace];
                minDistance = normals[minFace].w;

                glm::vec3 support = Support(colliderA, colliderB, minNormal);
                float sDistance = glm::dot(minNormal, support);

                if (abs(sDistance - minDistance) >= 0.001f) {
                    minDistance = FLT_MAX;
                    std::vector<std::pair<size_t, size_t>> uniqueEdges;

                    for (size_t i = 0; i < normals.size(); i++) {
                        if (Simplex::SameDirection(normals[i], support)) {
                            size_t f = i * 3;

                            AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
                            AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
                            AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

                            faces[f + 2] = faces.back(); faces.pop_back();
                            faces[f + 1] = faces.back(); faces.pop_back();
                            faces[f] = faces.back(); faces.pop_back();

                            normals[i] = normals.back(); normals.pop_back();

                            i--;
                        }
                    }
                    std::vector<size_t> newFaces;
                    for (auto [edgeIndex1, edgeIndex2] : uniqueEdges) {
                        newFaces.push_back(edgeIndex1);
                        newFaces.push_back(edgeIndex2);
                        newFaces.push_back(polytope.size());
                    }

                    polytope.push_back(support);

                    auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);
                    float oldMinDistance = FLT_MAX;
                    for (size_t i = 0; i < normals.size(); i++) {
                        if (normals[i].w < oldMinDistance) {
                            oldMinDistance = normals[i].w;
                            minFace = i;
                        }
                    }

                    if (newNormals[newMinFace].w < oldMinDistance) {
                        minFace = newMinFace + normals.size();
                    }

                    faces.insert(faces.end(), newFaces.begin(), newFaces.end());
                    normals.insert(normals.end(), newNormals.begin(), newNormals.end());
                }
            }
        }

        if (minDistance == FLT_MAX) {
            minDistance = normals[minFace].w;
        }

        colInfo.Normal = minNormal;
        colInfo.PenetrationDepth = minDistance + 0.001f;

        return true;
    }

    std::pair<std::vector<glm::vec4>, size_t> CollisionEngine::GetFaceNormals(std::vector<glm::vec3>& polytope, std::vector<size_t>& faces)
    {
        std::vector<glm::vec4> normals;
        size_t minTriangle = 0;
        float  minDistance = FLT_MAX;

        for (size_t i = 0; i < faces.size(); i += 3) {
            glm::vec3 a = polytope[faces[i]];
            glm::vec3 b = polytope[faces[i + 1]];
            glm::vec3 c = polytope[faces[i + 2]];

            glm::vec3 normal = glm::cross((b - a), (c - a));
            normal = glm::normalize(normal);
            float distance = glm::dot(normal, a);

            if (distance < 0) {
                normal *= -1;
                distance *= -1;
            }

            normals.emplace_back(normal.x, normal.y, normal.z, distance);

            if (distance < minDistance) {
                minTriangle = i / 3;
                minDistance = distance;
            }
        }



        return { normals, minTriangle };
    }
    void CollisionEngine::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b)
    {
        auto reverse = std::find(
            edges.begin(),
            edges.end(),
            std::make_pair(faces[b], faces[a])
        );

        if (reverse != edges.end()) {
            edges.erase(reverse);
        }

        else {
            edges.emplace_back(faces[a], faces[b]);
        }
    }

    void CollisionEngine::CalculateContactPoints(Collider& contactObject1, Collider& contactObject2, CollisionInfo& colInfo) {
        auto findOrigin = [](const std::vector<std::pair<glm::vec3, float>>& points) {
            glm::vec3 origin{ 0,0,0 };
            for (size_t i = 0; i < points.size(); i++) {
                origin += points[i].first;
            }
            origin /= points.size();
            return origin;
            };
        auto compareAngle = [](const std::pair<glm::vec3, float>& pA, const std::pair<glm::vec3, float>& pB) {
            if (pA.second < pB.second) {
                return true;
            }
            return false;
            };
        auto findContactPoints = [](Collider& contactObject, Plane contactPlane, std::vector<std::pair<glm::vec3, float>>& contactBuf) {
            auto vertices = contactObject.GetVertices();

            for (size_t i = 0; i < vertices->size(); i += 3)
            {
                glm::vec3 point{ (*vertices)[i + 0],(*vertices)[i + 1],(*vertices)[i + 2] };
                point = glm::ToWorldSpace(point, contactObject.GetParentObject()->transform.GetTransformMatrix());

                float distance = glm::abs(glm::GetVertexToPlaneDistance(point, contactPlane.P1, contactPlane.Normal));
                if (distance > 0.005f)
                    continue;

                contactBuf.push_back({ point,0 });
            }
            };
        auto calculateAngles = [findOrigin](std::vector<std::pair<glm::vec3, float>>& contactPoints, glm::vec3 normal) {
            glm::vec3 originA = findOrigin(contactPoints);
            glm::vec3 refVector = contactPoints[0].first - originA;
            for (size_t i = 1; i < contactPoints.size(); i++) {
                glm::vec3 originToPoint = contactPoints[i].first - originA;
                float u = glm::dot(normal, glm::cross(refVector, originToPoint));
                float angle = glm::GetAngle(refVector, originToPoint) * 180.0f / glm::pi<float>();

                //if u <= 0 than point is left
                if (u <= 0.001f) {
                    contactPoints[i].second = angle;
                }
                else
                {
                    contactPoints[i].second = angle + 180;
                }
            }
            };

        //Point and angle
        std::vector<std::pair<glm::vec3, float>> contactPointsA; contactPointsA.reserve(4);
        std::vector<std::pair<glm::vec3, float>> contactPointsB; contactPointsB.reserve(4);

        colInfo.Normal = glm::normalize(colInfo.Normal);
        glm::vec3 point = glm::ToWorldSpace(contactObject1.FindFurthestPoint(colInfo.Normal), contactObject1.GetParentObject()->transform.GetTransformMatrix());
        Plane contactPlane{ point, colInfo.Normal };

        //Finding contact points from shape A
        findContactPoints(contactObject1, contactPlane, contactPointsA);

        //Finding contact points from shape B
        findContactPoints(contactObject2, contactPlane, contactPointsB);

        if (contactPointsA.size() == 0) {
            for (size_t i = 0; i < contactPointsB.size(); i++)
            {
                colInfo.CollisionPoints.push_back(contactPointsB[i].first);
            }
            return;
        }
        if (contactPointsB.size() == 0) {
            for (size_t i = 0; i < contactPointsA.size(); i++)
            {
                colInfo.CollisionPoints.push_back(contactPointsA[i].first);
            }
            return;
        }

        //Vertex to face contact
        if (contactPointsA.size() == 1) {
            colInfo.CollisionPoints.push_back(contactPointsA[0].first);
            return;
        }
        else if (contactPointsB.size() == 1) {
            colInfo.CollisionPoints.push_back(contactPointsB[0].first);
            return;
        }

        //calculate angle
        calculateAngles(contactPointsA, colInfo.Normal);
        calculateAngles(contactPointsB, colInfo.Normal);

        //Rebuild shapes correctly(by clock)
        std::sort(contactPointsA.begin(), contactPointsA.end(), compareAngle);
        std::sort(contactPointsB.begin(), contactPointsB.end(), compareAngle);

        std::vector<glm::vec3> realContactPoints;
        CheckIntersection(contactPointsA, contactPointsB, colInfo.Normal, realContactPoints);

        //All point shape B outside shape A
        //So All points shape A inside shapeB
        if (realContactPoints.size() == 0) {
            //std::cout << " Not\n";
            CheckIntersection(contactPointsB, contactPointsA, colInfo.Normal, realContactPoints);
        }

        std::cout << realContactPoints.size() << " size\t" << " End\n";

        colInfo.CollisionPoints = { realContactPoints.begin(), realContactPoints.end() };

        auto* tempMeshesBuffer = Core::World::GetSystemData<AnomalyEngine::TempMeshesBuffer>("TempMeshesBuffer");

        for (auto it : colInfo.CollisionPoints) {
            if (tempMeshesBuffer) {
                tempMeshesBuffer->Draw<AnomalyEngine::Sphere>(it, glm::vec3{ 0,0,0 }, glm::vec3{0.5,0.5,0.5});
            }
        }
    }

    void CollisionEngine::CheckIntersection(
        const std::vector<std::pair<glm::vec3, float>>& contactPointsA,
        const std::vector<std::pair<glm::vec3, float>>& contactPointsB,
        glm::vec3 normal,
        std::vector<glm::vec3>& contactPointsBuf) {


        for (size_t it = 0; it < contactPointsB.size(); it++)
        {
            size_t itSecondP = it + 1;
            if (itSecondP == contactPointsB.size()) {
                itSecondP = 0;
            }

            //We assume that the first point is inside
            unsigned int passedCount = 1;

            //Check if first point inside shape
            for (size_t jt = 0; jt < contactPointsA.size(); jt++) {
                size_t jtSecondP = jt + 1;
                if (jtSecondP == contactPointsA.size()) {
                    jtSecondP = 0;
                }

                glm::vec3 vct = contactPointsB[it].first - contactPointsA[jt].first;
                glm::vec3 edgeVector = contactPointsA[jtSecondP].first - contactPointsA[jt].first;

                glm::vec3 norm = glm::cross(glm::normalize(edgeVector), normal);

                if (glm::dot(norm, vct) < 0) {
                    passedCount--;
                    break;
                }
            }
            if (passedCount == 1)
                contactPointsBuf.push_back(contactPointsB[it].first);


            //Check if second point inside shape
            //We assume that the second point is inside
            passedCount++;
            for (size_t jt = 0; jt < contactPointsA.size(); jt++) {
                size_t jtSecondP = jt + 1;
                if (jtSecondP == contactPointsA.size()) {
                    jtSecondP = 0;
                }
                glm::vec3 vct = contactPointsB[itSecondP].first - contactPointsA[jt].first;
                glm::vec3 edgeVector = contactPointsA[jtSecondP].first - contactPointsA[jt].first;

                glm::vec3 norm = glm::normalize(glm::cross(glm::normalize(edgeVector), normal));

                if (glm::dot(norm, vct) < 0) {
                    passedCount--;
                    break;
                }
            }

            //all points of current line is inside shape
            //We ignore second point because it will be added on next iteration
            if (passedCount == 2) {
                //contactPointsBuf.push_back(contactPointsB[itSecondP].first);
                continue;
            }


            ////all points of current line is outside shape
            //if (passedCount == 0 && !(contactPointsA.size() == 2 && contactPointsB.size() == 2))
            //    continue;

            //Check if line separate shape
            for (size_t jt = 0; jt < contactPointsA.size(); jt++) {
                size_t jtSecondP = jt + 1;
                if (jtSecondP == contactPointsA.size()) {
                    jtSecondP = 0;
                }

                glm::vec3 projectPoint;

                bool notParallel = glm::ClosestPointBetweenAxis(
                    { contactPointsB[it].first, contactPointsB[itSecondP].first },
                    { contactPointsA[jt].first, contactPointsA[jtSecondP].first }, projectPoint);

                if (!notParallel)
                    continue;

                float vct1 = glm::length2(contactPointsB[it].first - projectPoint);
                float vct2 = glm::length2(contactPointsB[itSecondP].first - projectPoint);

                float lengthAxisB = glm::length2(contactPointsB[itSecondP].first - contactPointsB[it].first);
                float lengthAxisA = glm::length2(contactPointsA[jtSecondP].first - contactPointsA[jt].first);

                if (vct1 > lengthAxisA || vct2 > lengthAxisA)
                    continue;

                if (vct1 > lengthAxisB || vct2 > lengthAxisB)
                    continue;

                contactPointsBuf.push_back(projectPoint);
            }
        }
    }
}
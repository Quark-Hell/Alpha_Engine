#include "Collision.h"

#include "World.h"
#include "Modules/Physics.h"
#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"
#include "Object.h"

#include "Plane.h"

Simplex::Simplex(std::array<Vector3, 4> points, unsigned size) {
    Simplex::_points = points;
    Simplex::_size = size;
}
void Simplex::PushFront(Vector3 point) {
    _points = { point, _points[0], _points[1], _points[2] };
    _size = std::min(_size + 1, 4u);
}
unsigned Simplex::GetSize() {
    return _size;
}

bool Simplex::NextSimplex(Simplex& points, Vector3& direction) {
    switch (points.GetSize()) {
    case 2: return Line(points, direction);
    case 3: return Triangle(points, direction);
    case 4: return Tetrahedron(points, direction);
    }

    // never should be here
    return false;
}
bool Simplex::SameDirection(const Vector3& direction, const Vector3& ao) {
    return Vector3::DotProduct(direction,ao) > 0;
}

bool Simplex::Line(Simplex& points, Vector3& direction) {
    Vector3 a = points[0];
    Vector3 b = points[1];

    Vector3 ab = b - a;
    Vector3 ao = -a;

    if (SameDirection(ab, ao)) {
        direction = ab.CrossProduct(ao).CrossProduct(ab);
    }

    else {
        points = { a };
        direction = ao;
    }

    return false;
}
bool Simplex::Triangle(Simplex& points, Vector3& direction) {
    Vector3 a = points[0];
    Vector3 b = points[1];
    Vector3 c = points[2];

    Vector3 ab = b - a;
    Vector3 ac = c - a;
    Vector3 ao = -a;

    Vector3 abc = ab.CrossProduct(ac);

    if (SameDirection(abc.CrossProduct(ac), ao)) {
        if (SameDirection(ac, ao)) {
            points = { a, c };
            direction = ac.CrossProduct(ao).CrossProduct(ac);
        }

        else {
            return Line(points = { a, b }, direction);
        }
    }

    else {
        if (SameDirection(ab.CrossProduct(abc), ao)) {
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
bool Simplex::Tetrahedron(Simplex& points, Vector3& direction) {
    Vector3 a = points[0];
    Vector3 b = points[1];
    Vector3 c = points[2];
    Vector3 d = points[3];

    Vector3 ab = b - a;
    Vector3 ac = c - a;
    Vector3 ad = d - a;
    Vector3 ao = -a;

    Vector3 abc = ab.CrossProduct(ac);
    Vector3 acd = ac.CrossProduct(ad);
    Vector3 adb = ad.CrossProduct(ab);

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

/*Maybe need refactoring*/
void Collision::CollisionLoop() {
    //Clear collision Info
    for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
    {
        std::shared_ptr<RigidBody> RigidModule =
            std::static_pointer_cast<RigidBody>(World::ObjectsOnScene[it]->GetModuleByType(RigidBodyType));

        if (RigidModule != nullptr) {
            RigidModule->ClearCollisinInfo();
        }
    }

    std::shared_ptr<MeshCollider> colliderA;
    std::shared_ptr<MeshCollider> colliderB;

    for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            colliderA = std::dynamic_pointer_cast<MeshCollider>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));

            for (size_t kt = 1; kt < World::ObjectsOnScene.size(); kt++)
            {
                for (size_t mt = 0; mt < World::ObjectsOnScene[kt]->GetCountOfModules(); mt++)
                {
                    colliderB = std::dynamic_pointer_cast<MeshCollider>(World::ObjectsOnScene[kt]->GetModuleByIndex(mt));

                    if (colliderA == colliderB)
                        continue;

                    if (colliderA == nullptr || colliderB == nullptr)
                        continue;

                    Collision::GJK(*colliderA, *colliderB);
                }
            }
        }
    }
}


Vector3 Collision::Support(Geometry& colliderA, Geometry& colliderB, Vector3 direction)
{
    return colliderA.FindFurthestPoint(direction)
        - colliderB.FindFurthestPoint(-direction);
}

bool Collision::GJK(Geometry& colliderA, Geometry& colliderB) {
    CollisionInfo colInfo;

    // Get initial support point in any direction
    Vector3 support = Support(colliderA, colliderB, {1,0,0});

    // Simplex is an array of points, max count is 4
    Simplex points;
    points.PushFront(support);

    // New direction is towards the origin
    Vector3 direction = -support;

    for (unsigned int i = 0; i < Collision::GJKaccurate; i++) {
        support = Support(colliderA, colliderB, direction);

        if (support.DotProduct(direction) < 0) {
            return false; // no collision
        }

        points.PushFront(support);

        if (Simplex::NextSimplex(points, direction)) {
            std::shared_ptr<RigidBody> rb1 = std::dynamic_pointer_cast<RigidBody>(colliderA.GetParentObject()->GetModuleByType(ModulesList::RigidBodyType));
            std::shared_ptr<RigidBody> rb2 = std::dynamic_pointer_cast<RigidBody>(colliderB.GetParentObject()->GetModuleByType(ModulesList::RigidBodyType));



            if (rb1 != nullptr && rb2 == nullptr) {
                if (Collision::EPA(points, colliderA, colliderB, colInfo)) {
                    //Vector3 nowPos = colliderA.GetParentObject()->GetPosition();

                    rb1->_pullingVectors.push_back(-colInfo.Normal * colInfo.PenetrationDepth);

                    colliderA.GetParentObject()->AddPosition(-colInfo.Normal * colInfo.PenetrationDepth);
                    Collision::CalculateContactPoints(colliderA, colliderB, colInfo);

                    rb1->AddContactPoints(colInfo.collisionPoints);
                    rb1->_hasCollision = true;

                    //colliderA.GetParentObject()->SetPosition(nowPos);

                    Physics::Contact(*rb1, -colInfo.Normal);
                    std::cout << "contact";

                    return true;
                }
            }
            else if (rb1 == nullptr && rb2 != nullptr) {
                if (Collision::EPA(points, colliderA, colliderB, colInfo)) {
                    //Vector3 nowPos = colliderB.GetParentObject()->GetPosition();
            
                    rb2->_pullingVectors.push_back(colInfo.Normal * colInfo.PenetrationDepth);
            
                    colliderB.GetParentObject()->AddPosition(colInfo.Normal * colInfo.PenetrationDepth);
                    Collision::CalculateContactPoints(colliderA, colliderB, colInfo);
            
                    rb2->AddContactPoints(colInfo.collisionPoints);
                    rb2->_hasCollision = true;
            
                    //colliderB.GetParentObject()->SetPosition(nowPos);

                    Physics::Contact(*rb2, colInfo.Normal);
                    std::cout << "contact";

                    return true;
                }
            

            }
            else if (rb1 != nullptr && rb2 != nullptr) {
                if (Collision::EPA(points, colliderB, colliderA, colInfo)) {
                    Vector3 nowPos = colliderA.GetParentObject()->GetPosition();

                    rb1->_pullingVectors.push_back(-colInfo.Normal * colInfo.PenetrationDepth * 0.5f);
                    rb2->_pullingVectors.push_back(colInfo.Normal * colInfo.PenetrationDepth * 0.5f);

                    colliderA.GetParentObject()->AddPosition(colInfo.Normal * colInfo.PenetrationDepth);
                    Collision::CalculateContactPoints(colliderB, colliderA, colInfo);

                    rb1->AddContactPoints(colInfo.collisionPoints);
                    rb2->AddContactPoints(colInfo.collisionPoints);

                    rb1->_hasCollision = true;
                    rb2->_hasCollision = true;

                    colliderA.GetParentObject()->SetPosition(nowPos);
                    Physics::Contact(*rb1, *rb2, -colInfo.Normal);

                    return true;
                }


            }
            return true;
        }
    }
    return false;
}
bool Collision::EPA(Simplex& simplex, Geometry& colliderA, Geometry& colliderB, CollisionInfo& colInfo)
{
    std::vector<Vector3> polytope(simplex.begin(), simplex.end());
    std::vector<size_t>  faces = {
        0, 1, 2,
        0, 3, 1,
        0, 2, 3,
        1, 3, 2
    };

    // list: vector4(normal, distance), index: min distance
    auto [normals, minFace] = GetFaceNormals(polytope, faces);

    Vector3 minNormal;
    float   minDistance = FLT_MAX;

    for (unsigned int i = 0; i < Collision::EPAaccurate; i++) {
        if (minDistance == FLT_MAX) {
            minNormal = normals[minFace];
            minDistance = normals[minFace].W;

            Vector3 support = Support(colliderA, colliderB, minNormal);
            float sDistance = minNormal.DotProduct(support);

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
                    if (normals[i].W < oldMinDistance) {
                        oldMinDistance = normals[i].W;
                        minFace = i;
                    }
                }

                if (newNormals[newMinFace].W < oldMinDistance) {
                    minFace = newMinFace + normals.size();
                }

                faces.insert(faces.end(), newFaces.begin(), newFaces.end());
                normals.insert(normals.end(), newNormals.begin(), newNormals.end());
            }
        }
    }

    if (minDistance == FLT_MAX) {
        minDistance = normals[minFace].W;
    }

    colInfo.Normal = minNormal;
    colInfo.PenetrationDepth = minDistance + 0.001f;

    return true;
}

std::pair<std::vector<Vector4>, size_t> Collision::GetFaceNormals(std::vector<Vector3>& polytope,std::vector<size_t>& faces)
{
    std::vector<Vector4> normals;
    size_t minTriangle = 0;
    float  minDistance = FLT_MAX;

    for (size_t i = 0; i < faces.size(); i += 3) {
        Vector3 a = polytope[faces[i]];
        Vector3 b = polytope[faces[i + 1]];
        Vector3 c = polytope[faces[i + 2]];

        Vector3 normal = (b - a).CrossProduct(c - a);
        normal.NormilizeSelf();
        float distance = normal.DotProduct(a);

        if (distance < 0) {
            normal *= -1;
            distance *= -1;
        }

        normals.emplace_back(normal.X,normal.Y,normal.Z, distance);
   
        if (distance < minDistance) {
            minTriangle = i / 3;
            minDistance = distance;
        }
    }



    return { normals, minTriangle };
}
void Collision::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges,std::vector<size_t>& faces,size_t a,size_t b)
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

void Collision::CalculateContactPoints(Geometry& contactObject1, Geometry& contactObject2, CollisionInfo& colInfo) {
    auto findOrigin = [](const std::vector<std::pair<Vector3, float>>& points) {
        Vector3 origin{ 0,0,0 };
        for (size_t i = 0; i < points.size(); i++) {
            origin += points[i].first;
        }
        origin /= points.size();
        return origin;
    };
    auto compareAngle = [](const std::pair<Vector3, float>& pA, const std::pair<Vector3, float>& pB) {
        if (pA.second < pB.second) {
            return true;
        }
        return false;
    };
    auto findContactPoints = [](Geometry& contactObject, Plane contactPlane, std::vector<std::pair<Vector3, float>>& contactBuf) {  
        for (size_t i = 0; i < contactObject._vertex->size(); i += 3)
        {
            Vector3 point{ (*contactObject._vertex)[i + 0],(*contactObject._vertex)[i + 1],(*contactObject._vertex)[i + 2] };
            point += contactObject.GetParentObject()->GetPosition();

            float distance = Vector3::GetVertexToPlaneDistance(point, contactPlane.P1, contactPlane.Normal);
            if (distance > 0.005f)
                continue;

            contactBuf.push_back({ point,0 });
        }
    };
    auto calculateAngles = [findOrigin](std::vector<std::pair<Vector3, float>>& contactPoints, Vector3 normal) {
        Vector3 originA = findOrigin(contactPoints);
        Vector3 refVector = contactPoints[0].first - originA;
        for (size_t i = 1; i < contactPoints.size(); i++) {
            Vector3 originToPoint = contactPoints[i].first - originA;
            float u = Vector3::DotProduct(normal, Vector3::CrossProduct(refVector, originToPoint));
            float angle = Vector3::GetAngle(refVector, originToPoint) * 180.0f / M_PI;

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
    std::vector<std::pair<Vector3, float>> contactPointsA; contactPointsA.reserve(4);
    std::vector<std::pair<Vector3, float>> contactPointsB; contactPointsB.reserve(4);

    colInfo.Normal.NormilizeSelf();
    Plane contactPlane{ contactObject1.FindFurthestPoint(colInfo.Normal), colInfo.Normal };

    //Finding contact points from shape A
    findContactPoints(contactObject1, contactPlane, contactPointsA);

    //Finding contact points from shape B
    findContactPoints(contactObject2, contactPlane, contactPointsB);

    if (contactPointsA.size() == 0) {
        for (size_t i = 0; i < contactPointsB.size(); i++)
        {
            colInfo.collisionPoints.push_back(contactPointsB[i].first);
        }
        return;
    }
    if (contactPointsB.size() == 0) {
        for (size_t i = 0; i < contactPointsA.size(); i++)
        {
            colInfo.collisionPoints.push_back(contactPointsA[i].first);
        }
        return;
    }

    //Vertex to face contact
    if (contactPointsA.size() == 1) {
        colInfo.collisionPoints.push_back(contactPointsA[0].first);
        return;
    }
    else if (contactPointsB.size() == 1) {
        colInfo.collisionPoints.push_back(contactPointsB[0].first);
        return;
    }

    //calculate angle
    calculateAngles(contactPointsA, colInfo.Normal);
    calculateAngles(contactPointsB, colInfo.Normal);

    //Rebuild shapes correctly(by clock)
    std::sort(contactPointsA.begin(), contactPointsA.end(), compareAngle);
    std::sort(contactPointsB.begin(), contactPointsB.end(), compareAngle);

    std::vector<Vector3> realContactPoints;
    CheckIntersection(contactPointsA, contactPointsB, colInfo.Normal, realContactPoints);

    //All point shape B outside shape A
    //So All points shape A inside shapeB
    if (realContactPoints.size() == 0) {
        //std::cout << " Not\n";
        CheckIntersection(contactPointsB, contactPointsA, colInfo.Normal, realContactPoints);
    }

    std::cout << realContactPoints.size() << " size\t" << " End\n";

    colInfo.collisionPoints = { realContactPoints.begin(), realContactPoints.end() };
}

void Collision::CheckIntersection(
    std::vector<std::pair<Vector3, float>>& contactPointsA,
    std::vector<std::pair<Vector3, float>>& contactPointsB,
    Vector3 normal,
    std::vector<Vector3>& contactPointsBuf) {


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

            Vector3 vct = contactPointsB[it].first - contactPointsA[jt].first;
            Vector3 edgeVector = contactPointsA[jtSecondP].first - contactPointsA[jt].first;

            Vector3 norm = Vector3::CrossProduct(Vector3::GetNormalize(edgeVector), normal);

            if (Vector3::DotProduct(norm, vct) < 0) {
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
            Vector3 vct = contactPointsB[itSecondP].first - contactPointsA[jt].first;
            Vector3 edgeVector = contactPointsA[jtSecondP].first - contactPointsA[jt].first;

            Vector3 norm = Vector3::GetNormalize(Vector3::CrossProduct(Vector3::GetNormalize(edgeVector), normal));

            if (Vector3::DotProduct(norm, vct) < 0) {
                passedCount--;
                break;
            }
        }

        //all points of current line is inside shape
        if (passedCount == 2)
            continue;

        ////all points of current line is outside shape
        //if (passedCount == 0 && !(contactPointsA.size() == 2 && contactPointsB.size() == 2))
        //    continue;

        //Check if line separate shape
        for (size_t jt = 0; jt < contactPointsA.size(); jt++) {
            size_t jtSecondP = jt + 1;
            if (jtSecondP == contactPointsA.size()) {
                jtSecondP = 0;
            }

            Vector3 projectPoint;

            bool notParallel = Vector3::ClosetPointBetweenAxis(
                { contactPointsB[it].first, contactPointsB[itSecondP].first },
                { contactPointsA[jt].first, contactPointsA[jtSecondP].first }, projectPoint);

            if (!notParallel)
                continue;

            float vct1 = Vector3::GetNonSqrtMagnitude(contactPointsB[it].first - projectPoint);
            float vct2 = Vector3::GetNonSqrtMagnitude(contactPointsB[itSecondP].first - projectPoint);

            float lengthAxisB = Vector3::GetNonSqrtMagnitude(contactPointsB[itSecondP].first - contactPointsB[it].first);
            float lengthAxisA = Vector3::GetNonSqrtMagnitude(contactPointsA[jtSecondP].first - contactPointsA[jt].first);

            if (vct1 > lengthAxisA || vct2 > lengthAxisA)
                continue;

            if (vct1 > lengthAxisB || vct2 > lengthAxisB)
                continue;

            contactPointsBuf.push_back(projectPoint);
        }
    }
}
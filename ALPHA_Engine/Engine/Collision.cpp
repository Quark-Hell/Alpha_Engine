#include "Collision.h"

#include "World.h"
#include "Modules/Physics.h"
#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"
#include "Object.h"

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

    Vector3 cr1 = abc.CrossProduct(ac);
    Vector3 cr2 = ab.CrossProduct(abc);

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
    for (size_t it = 0; it < World::ObjectsOnScene.size() - 1; it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            MeshCollider* collider = dynamic_cast<MeshCollider*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));

            if (collider != nullptr && collider->GetType() == ModulesList::MeshColliderType) {
                collider->collisionInfo.HasCollision = false;
            }
        }
    }


    CollisionInfo points;

    Geometry* colliderA;
    Geometry* colliderB;

    for (size_t it = 0; it < World::ObjectsOnScene.size()-1; it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            ModulesList typeA = World::ObjectsOnScene[it]->GetModuleByIndex(jt)->GetType();

            switch (typeA)
            {
            case MeshColliderType:
                colliderA = dynamic_cast<Geometry*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));
                break;
            case BoxColliderType:
                colliderA = dynamic_cast<Geometry*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));
                break;
            default:
                continue;
                break;
            }

            
            for (size_t kt = 1; kt < World::ObjectsOnScene.size(); kt++)
            {
                for (size_t mt = 0; mt < World::ObjectsOnScene[kt]->GetCountOfModules(); mt++)
                {
                    ModulesList typeB = World::ObjectsOnScene[kt]->GetModuleByIndex(mt)->GetType();

                    switch (typeB)
                    {
                    case MeshColliderType:
                        colliderB = dynamic_cast<Geometry*>(World::ObjectsOnScene[kt]->GetModuleByIndex(mt));
                        break;
                    case BoxColliderType:
                        colliderB = dynamic_cast<Geometry*>(World::ObjectsOnScene[kt]->GetModuleByIndex(mt));
                        break;
                    default:
                        continue;
                        break;
                    }

                    if (colliderA == colliderB)
                        continue;
                    
                    if (typeA == ModulesList::MeshColliderType && typeB == MeshColliderType) {
                        Collision::GJK(*colliderA, *colliderB, points);
                    }
                    else if (typeA == ModulesList::BoxColliderType && typeB == BoxColliderType) {
                        Collision::GJK(*colliderA, *colliderB, points);
                    }
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

bool Collision::GJK(Geometry& colliderA, Geometry& colliderB, CollisionInfo& colPoints) {
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
            RigidBody* rb1 = dynamic_cast<RigidBody*>(colliderA.GetParentObject()->GetModuleByType(ModulesList::RigidBodyType));
            RigidBody* rb2 = dynamic_cast<RigidBody*>(colliderB.GetParentObject()->GetModuleByType(ModulesList::RigidBodyType));

            if (rb1 != nullptr && rb2 == nullptr) {
                colPoints = Collision::EPA(points, colliderA, colliderB);

                colliderA.GetParentObject()->AddPosition((-colPoints.Normal.X * colPoints.PenetrationDepth), (-colPoints.Normal.Y * colPoints.PenetrationDepth), (-colPoints.Normal.Z * colPoints.PenetrationDepth));
                colliderA.GetParentObject()->ApplyTransform();

                Physics::Contact(*rb1, -colPoints.Normal);
                //rb1->_movementVector = { 0,0,0 };
            }
            else if (rb1 == nullptr && rb2 != nullptr) {
                colPoints = Collision::EPA(points, colliderA, colliderB); 

                colliderB.GetParentObject()->AddPosition((colPoints.Normal.X * colPoints.PenetrationDepth), (colPoints.Normal.Y * colPoints.PenetrationDepth), (colPoints.Normal.Z * colPoints.PenetrationDepth));
                colliderB.GetParentObject()->ApplyTransform();

                Physics::Contact(*rb2, -colPoints.Normal);
                //rb2->_movementVector = { 0,0,0 };
            }
            else if (rb1 != nullptr && rb2 != nullptr) {
                colPoints = Collision::EPA(points, colliderB, colliderA);

                colliderA.GetParentObject()->AddPosition((colPoints.Normal.X * colPoints.PenetrationDepth), (colPoints.Normal.Y * colPoints.PenetrationDepth), (colPoints.Normal.Z * colPoints.PenetrationDepth));
                colliderA.GetParentObject()->ApplyTransform();

                Physics::Contact(*rb1, *rb2, -colPoints.Normal);
            }
            return true;
        }
    }
}
CollisionInfo Collision::EPA(Simplex& simplex, Geometry& colliderA, Geometry& colliderB)
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
        std::cout << std::endl << "not" << std::endl;
        minDistance = normals[minFace].W;
    }

    //TODO: 
    CollisionInfo pointsA;

    pointsA.Normal = minNormal;
    pointsA.PenetrationDepth = minDistance + 0.001f;
    pointsA.HasCollision = true;
    //pointsA.CollisionPoints = Collision::GetContactPoints(*colliderA, pointsA.Normal);

    CollisionInfo pointsB;
    
    pointsB.Normal = minNormal;
    pointsB.PenetrationDepth = minDistance + 0.001f;
    pointsB.HasCollision = true;
    //pointsB.CollisionPoints = Collision::GetContactPoints(*colliderB, pointsB.Normal);

    return pointsA;
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

std::shared_ptr<std::vector<float>> Collision::GetContactPoints(Geometry& geometry, Vector3 moveVector) {

    std::shared_ptr<std::vector<float>> ContactPoints = std::make_shared<std::vector<float>>();

    Vector3 vec = Vector3{ geometry._vertex[0], geometry._vertex[1] , geometry._vertex[2] };
    float maxDotProduct = Vector3::DotProduct(vec, moveVector);

    ContactPoints->push_back(geometry._vertex[0]);
    ContactPoints->push_back(geometry._vertex[1]);
    ContactPoints->push_back(geometry._vertex[2]);

    for (unsigned int i = 3; i < geometry._vertexCount * 3; i+=3) {
        vec = Vector3{ geometry._vertex[i], geometry._vertex[i + 1] , geometry._vertex[i + 2] };
        float currentDotProduct = Vector3::DotProduct(vec, moveVector);

        if (maxDotProduct < currentDotProduct) {
            maxDotProduct = currentDotProduct;

            ContactPoints->clear();
            ContactPoints->push_back(geometry._vertex[i]);
            ContactPoints->push_back(geometry._vertex[i + 1]);
            ContactPoints->push_back(geometry._vertex[i + 2]);
        }
        else if (Math::ApproximatelyEqual(maxDotProduct,currentDotProduct, 0.001)) {
            ContactPoints->push_back(geometry._vertex[i]);
            ContactPoints->push_back(geometry._vertex[i + 1]);
            ContactPoints->push_back(geometry._vertex[i + 2]);
        }
    }

    return ContactPoints;
}
#include "Collision.h"
#include "Modules/Geometry.cpp"
#include <set>

inline Simplex::Simplex(std::array<Vector3, 4> points, unsigned size) {
    Simplex::_points = points;
    Simplex::_size = size;
}
inline void Simplex::PushFront(Vector3 point) {
    _points = { point, _points[0], _points[1], _points[2] };
    _size = std::min(_size + 1, 4u);
}
inline unsigned Simplex::GetSize() {
    return _size;
}

inline bool Simplex::NextSimplex(Simplex& points, Vector3& direction) {
    switch (points.GetSize()) {
    case 2: return Line(points, direction);
    case 3: return Triangle(points, direction);
    case 4: return Tetrahedron(points, direction);
    }

    // never should be here
    return false;
}
inline bool Simplex::SameDirection(const Vector3& direction, const Vector3& ao) {
    return Vector3::DotProduct(direction,ao) > 0;
}

inline bool Simplex::Line(Simplex& points, Vector3& direction) {
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
inline bool Simplex::Triangle(Simplex& points, Vector3& direction) {
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
inline bool Simplex::Tetrahedron(Simplex& points, Vector3& direction) {
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

inline Collider::Collider() {
    Collider::Rename("Collider");
}
inline bool Collider::CreateConvexFrom—oncave(std::string link) {

}

/*Maybe need refactoring*/
inline void Collision::CollisionLoop() {
    CollisionPoints points;
    for (size_t it = 0; it < World::ObjectsOnScene.size()-1; it++)
    {
        for (size_t jt = 0; jt < World::ObjectsOnScene[it]->GetCountOfModules(); jt++)
        {
            Collider* colliderA = dynamic_cast<Collider*>(World::ObjectsOnScene[it]->GetModuleByIndex(jt));
            for (size_t kt = 1; kt < World::ObjectsOnScene.size(); kt++)
            {
                for (size_t mt = 0; mt < World::ObjectsOnScene[kt]->GetCountOfModules(); mt++)
                {
                    Collider* colliderB = dynamic_cast<Collider*>(World::ObjectsOnScene[kt]->GetModuleByIndex(mt));

                    if (colliderA != nullptr && colliderA->GetName() == "Collider" && colliderB != nullptr && colliderB->GetName() == "Collider" && colliderA != colliderB) {
                        if (Collision::GJK((Collider*)colliderA, (Collider*)colliderB, points)) {
                            colliderA->GetParentObject()->AddPosition(-(points.Normal.X * points.PenetrationDepth), -(points.Normal.Y * points.PenetrationDepth), -(points.Normal.Z * points.PenetrationDepth));
                            colliderA->GetParentObject()->ApplyTransform();
                        }
                    }
                }
            }

        }
    }


}

inline Vector3 Collision::Support(Collider* colliderA, Collider* colliderB, Vector3 direction) 
{
    return colliderA->FindFurthestPoint(direction)
        - colliderB->FindFurthestPoint(-direction);
}

inline bool Collision::GJK(Collider* colliderA, Collider* colliderB, CollisionPoints& colPoints) {
    // Get initial support point in any direction
    Vector3 support = Support(colliderA, colliderB, {1,0,0});

    // Simplex is an array of points, max count is 4
    Simplex points;
    points.PushFront(support);

    // New direction is towards the origin
    Vector3 direction = -support;

    while (true) {
        support = Support(colliderA, colliderB, direction);

        if (support.DotProduct(direction) < 0) {
            //printf("false");
            return false; // no collision
        }

        points.PushFront(support);

        if (Simplex::NextSimplex(points, direction)) {
            printf("true");
            colPoints = Collision::EPA(points, colliderA, colliderB);
            return true;
        }
    }
}
inline CollisionPoints Collision::EPA(Simplex& simplex, Collider* colliderA, Collider* colliderB)
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

    while (minDistance == FLT_MAX) {
        minNormal = normals[minFace];
        minDistance = normals[minFace].W;

        Vector3 support = Support(colliderA, colliderB, minNormal);
        float sDistance = minNormal.DotProduct(support);

        if (abs(sDistance - minDistance) > 0.001f) {
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
    CollisionPoints points;

    points.Normal = minNormal;
    points.PenetrationDepth = minDistance + 0.001f;
    points.HasCollision = true;

    return points;
}

inline std::pair<std::vector<Vector4>, size_t> Collision::GetFaceNormals(std::vector<Vector3>& polytope,std::vector<size_t>& faces)
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
inline void Collision::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges,std::vector<size_t>& faces,size_t a,size_t b)
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
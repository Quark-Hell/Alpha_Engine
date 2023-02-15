#include "Collision.h"
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

inline bool Collider::CreateCollider(std::string link) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + link.c_str();

    //TODO: Check if fbx
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    aiMesh* mesh = scene->mMeshes[0];

    Collider::_vertex.clear();
    Collider::_normals.clear();

    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
        Vector3 point;
        Vector3 normal;
        std::string hash;
        const int arr_len = 3;
        float vertArr[arr_len];

        if (mesh->HasPositions()) {
            point.X = mesh->mVertices[it].x;
            point.Y = mesh->mVertices[it].y;
            point.Z = mesh->mVertices[it].z;
        }

        if (mesh->HasNormals()) {
            normal.X = mesh->mNormals[it].x;
            normal.Y = mesh->mNormals[it].y;
            normal.Z = mesh->mNormals[it].z;
        }

        Collider::_vertex.push_back(point);
        Collider::_normals.push_back(normal);
    }

    Mesh::MakeUnique(&(Collider::_vertex));
    Mesh::MakeUnique(&(Collider::_normals));

    return true;
}

inline bool Collider::CreateConvexFromÑoncave(std::string link) {

}

inline Vector3 Collision::Support(Collider* colliderA, Collider* colliderB, Vector3 direction) 
{
    return colliderA->FindFurthestPoint(direction)
        - colliderB->FindFurthestPoint(-direction);
}

inline bool Collision::GJK(Collider* colliderA, Collider* colliderB) {
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
            printf("false");
            return false; // no collision
        }

        points.PushFront(support);

        if (Simplex::NextSimplex(points, direction)) {
            printf("true");
            return true;
        }
    }
}
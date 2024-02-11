#include "Geometry.h"

#include "Object.h"
#include "Alghoritms.h"

Geometry::Geometry() {

}
Geometry::~Geometry() {

}

Object* Geometry::GetParentObject() {
    return ParentObject;
}
void Geometry::SetParentObject(const Object& parent) {
    ParentObject = const_cast<Object*>(&parent);
}

void Geometry::ModuleAdded()
{
    //Geometry::_position = ParentObject->GetPosition();
    //Geometry::_rotation = ParentObject->GetRotation();
    //Geometry::_scale = ParentObject->GetScale();

    //TODO: Add copy origin
    //Geometry::_origin = ParentObject->geto();
}

ModulesList Geometry::GetType() {
    return GeometryType;
}

bool Geometry::Create(std::string linkToFBX) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    aiMesh* mesh = s->mMeshes[0];

    Geometry::_indices->resize(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
        }
    }

    Geometry::_vertexCount = mesh->mNumVertices;
    Geometry::_vertex = new float[Geometry::_vertexCount * 3];

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasPositions()) {
            Geometry::_vertex[it] = mesh->mVertices[it / 3].x;
            Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
            Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    Geometry::_normals->resize(Geometry::_vertexCount * 3);

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasNormals()) {
            (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
            (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
            (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
        }
    }


    Geometry::_isIndexed = true;
    //Mesh::MakeUnique();
    //Mesh::_isShifted = true;

    return true;
}

bool Geometry::Create(std::string linkToFBX, 
    bool initIndices,
    bool initVertex,
    bool initNormals,
    bool initTexCoord, 
    bool initMaterial)
{
    Geometry::_indices->clear();
    Geometry::_normals->clear();

    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s;
    aiMesh* mesh = s->mMeshes[0];

    if (initIndices) {
        s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

        Geometry::_indices->resize(mesh->mNumFaces * 3);

        for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
            for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
            {
                (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
            }
        }

        Geometry::_isIndexed = true;
    }
    else
    {
        s = importer.ReadFile(path, aiProcess_Triangulate);
        Geometry::_isIndexed = false;
    }

    if (mesh->HasPositions() && initVertex) {
        Geometry::_vertexCount = mesh->mNumVertices;
        Geometry::_vertex = new float[Geometry::_vertexCount * 3];
        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            Geometry::_vertex[it] = mesh->mVertices[it / 3].x;
            Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
            Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
    }


    if (mesh->HasNormals() && initNormals) {
        Geometry::_normals->resize(Geometry::_vertexCount * 3);

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
            (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
            (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
        }
    }

    //Mesh::_isShifted = true;

    return true;
}

/*Recommended not use now. Work so slow*/
void Geometry::MakeUnique() {
    const int arr_len = 3;
    std::array<float, arr_len> buffer;
    
    unsigned int count = 0;
    
    std::unordered_map<std::string, std::array<float,arr_len>> uniqueMap;
    
    std::string hash;
    hash.resize(arr_len * sizeof(float));
    
    //delete same vertex by use hash map
    for (size_t it = 0; it < Geometry::_vertexCount * 3; it += 3)
    {
        //insert vert
        buffer[0] = Geometry::_vertex[it];
        buffer[1] = Geometry::_vertex[it + 1];
        buffer[2] = Geometry::_vertex[it + 2];
    
        memcpy((char*)hash.data(), &buffer, arr_len * sizeof(float));
    
        std::pair<std::string, std::array<float, arr_len>> vertPair(hash, buffer);
    
        uniqueMap.insert(vertPair);
    }
    
    Geometry::_vertexCount = uniqueMap.size();
    free(Geometry::_vertex);
    Geometry::_vertex = new float[Geometry::_vertexCount * 3];

    //int it = 0;
    //for (const auto& pair : uniqueMap) {
    //    if (it < Geometry::_vertexCount * 3) {
    //        Geometry::_vertex[it] = pair.second[0];
    //        Geometry::_vertex[it + 1] = pair.second[1];
    //        Geometry::_vertex[it + 2] = pair.second[2];
    //        it+=3;
    //    }
    //}

    for (size_t it = 0; it < uniqueMap.size() * 3; it+=3)
    {
        auto begin = uniqueMap.begin();
        std::advance(begin, it / 3);
    
        Geometry::_vertex[it]   = begin->second[0];
        Geometry::_vertex[it+1] = begin->second[1];
        Geometry::_vertex[it+2] = begin->second[2];
    }
}

/*Not work now*/
std::vector<Mesh*> Geometry::SeparateByLooseParts() {
    struct VertInfo
    {
        Vector3 Point;
        unsigned int TriangleID;
    };

    VertInfo vert{};
    std::unordered_map<std::string, VertInfo> vertMap;
    std::vector<bool> triangleBool;

    const int arr_len = 3;
    float vertArr[arr_len];

    std::string hash;
    hash.resize(arr_len * sizeof(float));

    Graph graph{ unsigned int(Geometry::_vertexCount)};

    unsigned int sizeBeforeInsert;

    //Create graph
    for (size_t it = 0; it < Geometry::_vertexCount * 3; it+=3)
    {
        vert.Point.X = _vertex[it];
        vert.Point.Y = _vertex[it + 1];
        vert.Point.Z = _vertex[it + 2];

        vert.TriangleID = it / 3;

        vertArr[0] = { vert.Point.X };
        vertArr[1] = { vert.Point.Y };
        vertArr[2] = { vert.Point.Z };

        sizeBeforeInsert = vertMap.size();

        //create hash
        memcpy((char*)hash.data(), vertArr, arr_len * sizeof(float));

        //insert hash
        std::pair<std::string, VertInfo> p(hash, vert);
        vertMap.insert(p);

        //chech if hash map not changed size after insert hash
        //is not changed => found same edges => found adjacent triangles
        if (sizeBeforeInsert == vertMap.size()) {
            unsigned int TriangleID = vertMap.find(hash)->second.TriangleID;
            graph.AddEdge(TriangleID, vert.TriangleID);
            graph.AddEdge(vert.TriangleID, TriangleID);
        }
    }

    triangleBool.resize(graph.GetAdjListSize());
    std::vector<std::vector<int>> separatedMesh;

    while (true) {
        int notConnected = -1;
        //Searches first triangle that does not belong to separated mesh
        for (size_t i = 0; i < triangleBool.size(); i++)
        {
            if (triangleBool[i] == false) {
                notConnected = i;
                break;
            }
        }
        if (notConnected == -1)
            break;

        separatedMesh.resize(separatedMesh.size() + 1);
        graph.BFS(notConnected, &separatedMesh[separatedMesh.size() - 1]);

        for (size_t i = 0; i < separatedMesh[separatedMesh.size() - 1].size(); i++)
        {
            triangleBool[separatedMesh[separatedMesh.size() - 1][i]] = true;
        }
    }

    std::vector<Mesh*> m;
    return m;
}

Vector3 Geometry::FindFurthestPoint(Vector3 direction) {
    Vector3 maxPoint = { 0,0,0 };
    float maxDistance = -FLT_MAX;
    Vector3 vertexPos = { 0,0,0 };

    for (size_t it = 0; it < Geometry::_vertexCount * 3; it+=3) {

        vertexPos.X = Geometry::_vertex[it];
        vertexPos.Y = Geometry::_vertex[it + 1];
        vertexPos.Z = Geometry::_vertex[it + 2];
  
        float distance = Vector3::DotProduct(vertexPos, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertexPos;
        }
    }

    Vector3 res = maxPoint + Geometry::GetParentObject()->GetPosition();
    return maxPoint + Geometry::GetParentObject()->GetPosition();
}

void Geometry::AddPosition(float X, float Y, float Z) {
    Geometry::_position.X += X;
    Geometry::_position.Y += Y;
    Geometry::_position.Z += Z;

    Geometry::_origin.X += X;
    Geometry::_origin.Y += Y;
    Geometry::_origin.Z += Z;

    Geometry::_isShifted = true;
}
void Geometry::AddPosition(Vector3 position) {
    Geometry::_position += position;
    Geometry::_origin += position;

    Geometry::_isShifted = true;
}
void Geometry::SetPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Geometry::_position;

    Geometry::AddPosition(direction);
}
void Geometry::SetPosition(Vector3 position) {
    Vector3 direction = position - Geometry::_position;

    Geometry::AddPosition(direction);
}

void Geometry::AddOriginPosition(float X, float Y, float Z) {
    Geometry::_origin.X += X;
    Geometry::_origin.Y += Y;
    Geometry::_origin.Z += Z;
}
void Geometry::AddOriginPosition(Vector3 position) {
    Geometry::_origin += position;
}

void Geometry::SetOriginPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Geometry::_origin;

    Geometry::AddOriginPosition(direction);
}
void Geometry::SetOriginPosition(Vector3 position) {
    Vector3 direction = position - Geometry::_origin;

    Geometry::AddOriginPosition(direction);
}


void Geometry::AddRotation(float X, float Y, float Z) {
    const float radX = M_PI / 180 * X;
    const float radY = M_PI / 180 * Y;
    const float radZ = M_PI / 180 * Z;

    Geometry::_rotation.X += X;
    Geometry::_rotation.Y += Y;
    Geometry::_rotation.Z += Z;

    Geometry::_isShifted = true;
}
void Geometry::AddRotation(Vector3 rotation) {
    const float radX = M_PI / 180 * rotation.X;
    const float radY = M_PI / 180 * rotation.Y;
    const float radZ = M_PI / 180 * rotation.Z;

    Geometry::_rotation.X += rotation.X;
    Geometry::_rotation.Y += rotation.Y;
    Geometry::_rotation.Z += rotation.Z;

    Geometry::_isShifted = true;
}

void Geometry::SetRotation(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Geometry::_rotation;

    Geometry::AddRotation(direction);
}
void Geometry::SetRotation(Vector3 rotation) {
    Vector3 direction = rotation - Geometry::_rotation;

    Geometry::AddRotation(direction);
}


void Geometry::SetScale(float X, float Y, float Z) {
    Geometry::_scale.X = X;
    Geometry::_scale.Y = Y;
    Geometry::_scale.Z = Z;

    Geometry::_isShifted = true;
}
void Geometry::SetScale(Vector3 scale) {
    Geometry::_scale.X = scale.X;
    Geometry::_scale.Y = scale.Y;
    Geometry::_scale.Z = scale.Z;

    Geometry::_isShifted = true;
}

void Geometry::ApplyTransformation()
{

}
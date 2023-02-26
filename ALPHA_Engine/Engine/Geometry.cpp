#include "Geometry.h"

inline Geometry::Geometry() {

}
inline Geometry::~Geometry() {

}

inline bool Geometry::Create(std::string linkToFBX) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
    aiMesh* mesh = s->mMeshes[0];

    Geometry::_vertexCount = mesh->mNumVertices;
    Geometry::_normalsCount = mesh->mNumVertices;

    Geometry::_vertex = new float[Geometry::_vertexCount * 3];
    Geometry::_normals = new float[Geometry::_normalsCount * 3];

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasPositions()) {
            Geometry::_vertex[it]     = mesh->mVertices[it / 3].x;
            Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
            Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
        if (mesh->HasNormals()) {
            Geometry::_normals[it]     = mesh->mNormals[it / 3].x;
            Geometry::_normals[it + 1] = mesh->mNormals[it / 3].y;
            Geometry::_normals[it + 2] = mesh->mNormals[it / 3].z;
        }
    }

    Geometry::MakeUnique();

    return true;
}

/*Recommended not use now. Work so slow*/
inline void Geometry::MakeUnique() {
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

    for (size_t it = 0; it < uniqueMap.size() * 3; it+=3)
    {
        auto begin = uniqueMap.begin();
        std::advance(begin, it / 3);

        Geometry::_vertex[it]   = begin->second[0];
        Geometry::_vertex[it+1] = begin->second[1];
        Geometry::_vertex[it+2] = begin->second[2];
    }
}

//Need refactoring
inline std::vector<Mesh*> Geometry::SeparateByLooseParts() {
    struct VertInfo
    {
        Vector3* Point;
        unsigned int TriangleID;
    };

    VertInfo vert;
    std::unordered_map<std::string, VertInfo> vertMap;
    std::vector<bool> triangleBool;

    const int arr_len = 3;
    float vertArr[arr_len];

    std::string hash;
    hash.resize(arr_len * sizeof(float));

    Graph graph{ unsigned int(Geometry::_vertexCount / 3)};

    unsigned int sizeBeforeInsert;

    //Create graph
    for (size_t it = 0; it < Geometry::_vertexCount * 3; it+=3)
    {
        vert.Point->X = _vertex[it];
        vert.Point->Y = _vertex[it + 1];
        vert.Point->Z = _vertex[it + 2];

        vert.TriangleID = it / 3;

        vertArr[0] = { vert.Point->X };
        vertArr[1] = { vert.Point->Y };
        vertArr[2] = { vert.Point->Z };

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
}

inline Vector3 Geometry::FindFurthestPoint(Vector3 direction) {
    Vector3 maxPoint = { 0,0,0 };
    float maxDistance = -FLT_MAX;
    Vector3* vertexPos = new Vector3;

    for (size_t it = 0; it < Geometry::_vertexCount * 3; it+=3) {

        vertexPos->X = Geometry::_vertex[it];
        vertexPos->Y = Geometry::_vertex[it + 1];
        vertexPos->Z = Geometry::_vertex[it + 2];
  
        float distance = Vector3::DotProduct(*vertexPos, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertexPos;
        }
    }

    return maxPoint + Geometry::GetParentObject()->GetPosition();
}

inline void Geometry::ApplyTransformation() {

}
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

    Geometry::_vertex.resize(mesh->mNumVertices);
    Geometry::_normals.resize(mesh->mNumVertices);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            Geometry::_indices.push_back(mesh->mFaces[it].mIndices[jt]);
        }
    }

    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
        Vector3 point;
        Vector3 normal;

        if (mesh->HasPositions()) {
            point.X = mesh->mVertices[it].x;
            point.Y = mesh->mVertices[it].y;
            point.Z = mesh->mVertices[it].z;

            Geometry::_vertex[it] = point;
        }

        if (mesh->HasNormals()) {
            normal.X = mesh->mNormals[it].x;
            normal.Y = mesh->mNormals[it].y;
            normal.Z = mesh->mNormals[it].z;

            Geometry::_normals[it] = normal;
        }
    }

    Geometry::MakeUnique();

    return true;
}

/*Recommended not use now. Work so slow*/
inline void Geometry::MakeUnique() {
	const int arr_len = 3;
	float buffer[arr_len];

	std::unordered_map<std::string, Vector3> uniqueMap;

	std::string hash;
	hash.resize(arr_len * sizeof(float));

    //delete same vertex by use hash map
	for (size_t it = 0; it < Geometry::_vertex.size(); it++)
	{
		//insert vert
		buffer[0] = Geometry::_vertex[it].X;
		buffer[1] = Geometry::_vertex[it].Y;
		buffer[2] = Geometry::_vertex[it].Z;

		memcpy((char*)hash.data(), buffer, arr_len * sizeof(float));

		std::pair<std::string, Vector3> vertPair(hash, Geometry::_vertex[it]);
		uniqueMap.insert(vertPair);
	}

    Geometry::_vertex.clear();
    for (size_t it = 0; it < uniqueMap.size(); it++)
    {
        auto begin = uniqueMap.begin();
        std::advance(begin, it);
        Geometry::_vertex.push_back(begin->second);
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

    Graph graph{ unsigned int(Geometry::_vertex.size() / 3)};

    unsigned int sizeBeforeInsert;

    //Create graph
    for (size_t it = 0; it < Geometry::_vertex.size(); it++)
    {
        vert.Point = &_vertex[it];
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

    for (size_t it = 0; it < Geometry::_vertex.size(); it++) {
        Vector3 vertexPos = Geometry::_vertex[it];
        float distance = Vector3::DotProduct(vertexPos, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertexPos;
        }
    }

    return maxPoint + Geometry::GetParentObject()->GetPosition();
}

inline void Geometry::ApplyTransformation() {
    for (size_t it = 0; it < Geometry::_vertex.size(); it++)
    {

    }
}
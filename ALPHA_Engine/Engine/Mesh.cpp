#include "Mesh.h"
#include "Alghoritms.cpp"

#pragma region Mesh Define
inline Mesh::Mesh() {
	Mesh::Rename("Mesh");
}

inline Mesh::~Mesh() {

}

inline bool Mesh::CreateMesh(std::string linkToFBX) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	aiMesh* mesh = s->mMeshes[0];

	Mesh::_vertex.clear();
	Mesh::_normals.clear();

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            Mesh::_indices.push_back(mesh->mFaces[it].mIndices[jt]);
        }
    }

	for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
		Vector3 point;
		Vector3 normal;  

		if (mesh->HasPositions()) {
			point.X = mesh->mVertices[it].x;
			point.Y = mesh->mVertices[it].y;
			point.Z = mesh->mVertices[it].z;

            Mesh::_vertex.push_back(point);
		}

		if (mesh->HasNormals()) {
			normal.X = mesh->mNormals[it].x;
			normal.Y = mesh->mNormals[it].y;
			normal.Z = mesh->mNormals[it].z;

            Mesh::_normals.push_back(normal);
		}

		//if (mesh->HasVertexColors(0))v.color = vec4(mesh->mColors[0][it]);
		//if (mesh->HasTextureCoords(0))v.uv = vec2(mesh->mTextureCoords[0][it]);
	}

    Mesh::_isShifted = true;

	return true;
}

inline void Mesh::DeleteMesh() {
	Mesh::_vertex.clear();
	Mesh::_normals.clear();
}

inline void Mesh::MakeUnique(std::vector<Vector3> *data) {
    const int arr_len = 3;
    float buffer[arr_len];

    std::unordered_map<std::string, Vector3> uniqueMap;

    std::string hash;
    hash.resize(arr_len * sizeof(float));

    for (size_t it = 0; it < (*data).size(); it++)
    {
        //insert vert
        buffer[0] = { (*data)[it].X };
        buffer[1] = { (*data)[it].Y };
        buffer[2] = { (*data)[it].Z };

        memcpy((char*)hash.data(), buffer, arr_len * sizeof(float));

        std::pair<std::string, Vector3> vertPair(hash, (*data)[it]);
        uniqueMap.insert(vertPair);
    }

    (*data).clear();
    (*data).clear();

    for (size_t it = 0; it < uniqueMap.size(); it++)
    {
        auto begin = uniqueMap.begin();
        std::advance(begin, it);
        (*data).push_back(begin->second);
    }
}

//Need refactoring
inline std::vector<Mesh*> Mesh::SeparateMesh() {
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

    Graph graph{ unsigned int(_vertex.size() / 3) };

    unsigned int sizeBeforeInsert;

    //Create graph
    for (size_t it = 0; it < _vertex.size(); it++)
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

inline Vector3 Mesh::FindFurthestPoint(Vector3 direction) {
    Vector3 maxPoint = { 0,0,0 };
    float maxDistance = -FLT_MAX;

    for (Vector3 vertex : Mesh::_vertex) {
        Vector3 vertexPos = vertex + Mesh::GetParentObject()->GetPosition();
        float distance = Vector3::DotProduct(vertexPos, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertexPos;
        }
    }

    return maxPoint;
}

inline void Mesh::ApplyTransformation() {
    for (size_t it = 0; it < Mesh::_vertex.size(); it++)
    {

    }
    for (size_t it = 0; it < Mesh::_normals.size(); it++)
    {

    }
}
#pragma endregion
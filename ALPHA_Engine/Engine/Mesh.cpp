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
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
	aiMesh* mesh = s->mMeshes[0];

	Mesh::_points.clear();
	Mesh::_normals.clear();

	for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
		Vector3 point;
		Vector3 normal;

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

		//if (mesh->HasVertexColors(0))v.color = vec4(mesh->mColors[0][it]);
		//if (mesh->HasTextureCoords(0))v.uv = vec2(mesh->mTextureCoords[0][it]);

		Mesh::_points.push_back(point);
		Mesh::_normals.push_back(normal);
	}

	return true;
}

inline void Mesh::DeleteMesh() {
	Mesh::_points.clear();
	Mesh::_normals.clear();
}

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
    float edgeArr[arr_len];

    std::string hash;
    hash.resize(arr_len * sizeof(float));

    Graph graph{ unsigned int(_points.size() / 3) };

    unsigned int sizeBeforeInsert;

    //Create graph
    for (size_t it = 0; it <= _points.size() - 1; it++)
    {
        vert.Point = &_points[it];
        vert.TriangleID = it / 3;

        edgeArr[0] = { vert.Point->X };
        edgeArr[1] = { vert.Point->Y };
        edgeArr[2] = { vert.Point->Z };

        sizeBeforeInsert = vertMap.size();

        //create hash
        memcpy((char*)hash.data(), edgeArr, arr_len * sizeof(float));

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
#pragma endregion
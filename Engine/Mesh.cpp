#include "Mesh.h"

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

	Mesh::Points.clear();
	Mesh::Normals.clear();

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

		Mesh::Points.push_back(point);
		Mesh::Normals.push_back(normal);
	}

	return true;
}

inline void Mesh::DeleteMesh() {
	Mesh::Points.clear();
	Mesh::Normals.clear();
}
#pragma endregion
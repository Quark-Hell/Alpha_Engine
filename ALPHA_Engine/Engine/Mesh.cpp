#include "Mesh.h"

#pragma region Mesh Define
inline Mesh::Mesh() {
	Mesh::Rename("Mesh");
}

inline Mesh::~Mesh() {

}

inline bool Mesh::Create(std::string linkToFBX) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	aiMesh* mesh = s->mMeshes[0];

	Geometry::_vertex.resize(mesh->mNumVertices);
	Geometry::_normals.resize(mesh->mNumVertices);
	Mesh::_indices.clear();

	for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
		for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
		{
			Mesh::_indices.push_back(mesh->mFaces[it].mIndices[jt]);
		}
	}

	for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
		if (mesh->HasPositions()) {
			Geometry::_vertex[it] = std::move(Vector3{	mesh->mVertices[it].x,
														mesh->mVertices[it].y,
														mesh->mVertices[it].z });
		}
		if (mesh->HasNormals()) {
			Geometry::_normals[it] = std::move(Vector3{ mesh->mNormals[it].x,
														mesh->mNormals[it].y,
														mesh->mNormals[it].z });
		}
	}

	//Mesh::MakeUnique();
	Mesh::_isShifted = true;

	return true;
}
#pragma endregion
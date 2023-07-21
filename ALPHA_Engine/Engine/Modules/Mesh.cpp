#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region Mesh Define
Mesh::Mesh() {

}
inline Mesh::~Mesh() {

}

inline ModulesList Mesh::GetType() {
	return ModulesList::MeshType;
}

bool Mesh::Create(std::string linkToFBX) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	aiMesh* mesh = s->mMeshes[0];

	Geometry::_vertexCount = mesh->mNumVertices;
	Geometry::_normalsCount = mesh->mNumVertices;
	Geometry::_indicesCount = mesh->mNumFaces*3;

	Geometry::_vertex = new float[Geometry::_vertexCount * 3];
	Geometry::_normals = new float[Geometry::_normalsCount * 3];
	Geometry::_indices = new unsigned int[Geometry::_indicesCount];

	for (size_t it = 0; it < mesh->mNumFaces; it++) {
		for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
		{
			Mesh::_indices[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
		}
	}

	for (size_t it = 0; it < mesh->mNumVertices * 3; it+=3) {
		if (mesh->HasPositions()) {
			Geometry::_vertex[it]	  =	mesh->mVertices[it / 3].x;
			Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
			Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
		}
		if (mesh->HasNormals()) {
			Geometry::_normals[it]	   = mesh->mNormals[it / 3].x;
			Geometry::_normals[it + 1] = mesh->mNormals[it / 3].y;
			Geometry::_normals[it + 2] = mesh->mNormals[it / 3].z;
		}
	}

	Mesh::_isIndexed = true;
	//Mesh::MakeUnique();
	//Mesh::_isShifted = true;

	for (size_t it = 0; it < Mesh::_vertexCount * 3; it++) {
		std::cout << Mesh::_vertex[it] << "\t" << Mesh::_vertex[it + 1] << "\t" << Mesh::_vertex[it + 2] << "\n";
	}

	return true;
}
#pragma endregion
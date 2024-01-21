#include "Mesh.h"

#include "SubModules/Material.h"

#pragma region Mesh Define
Mesh::Mesh() {
	Mesh::AddSubModule(MaterialType);
}
inline Mesh::~Mesh() {

}

inline ModulesList Mesh::GetType() {
	return ModulesList::MeshType;
}

void Mesh::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}


bool Mesh::AddSubModule(SubModulesList type) {
	std::shared_ptr<SubModule> someModule;

	switch (type)
	{
	case SubModuleType:
		return false;
		break;
	case MaterialType:
		if (Mesh::GetSubModuleByType(type))
			return false;

		someModule = std::dynamic_pointer_cast<SubModule>(std::make_shared<Material>());
		break;
	default:
		return false;
		break;
	}

	Mesh::_subModules.push_back(someModule);
	someModule->SetParentModule(*this);
	return true;
}
bool Mesh::AddSubModule(std::shared_ptr<SubModule> subModule) {
	SubModulesList type = subModule->GetType();

	switch (type)
	{
	case SubModuleType:
		return false;
		break;
	case MaterialType:
		if (Mesh::GetSubModuleByType(type))
			return false;
		break;
	default:
		return false;
		break;
	}

	Mesh::_subModules.push_back(subModule);
	subModule->SetParentModule(*this);
	return true;
}

bool Mesh::Create(std::string linkToFBX) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	aiMesh* mesh = s->mMeshes[0];

	Geometry::_indicesCount = mesh->mNumFaces * 3;
	Geometry::_indices = new unsigned int[Geometry::_indicesCount];

	for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
		for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
		{
			Geometry::_indices[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
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


	Geometry::_normalsCount = mesh->mNumVertices;
	Geometry::_normals = new float[Geometry::_normalsCount * 3];

	for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
		if (mesh->HasNormals()) {
			Geometry::_normals[it] = mesh->mNormals[it / 3].x;
			Geometry::_normals[it + 1] = mesh->mNormals[it / 3].y;
			Geometry::_normals[it + 2] = mesh->mNormals[it / 3].z;
		}
	}

	Material* mat = (Material*)Mesh::GetSubModuleByType(MaterialType).get();
	if (mat != nullptr) {
		mat->LoadTextureCoord(*s,0);
		mat->LoadMaterial(*s, 0);
	}


	Geometry::_isIndexed = true;
	//Mesh::MakeUnique();
	//Mesh::_isShifted = true;

	return true;
}
void Mesh::ApplyTransformation()
{

}
#pragma endregion
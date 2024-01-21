#include "Mesh.h"


#pragma region Mesh Define
Mesh::Mesh() {

}
inline Mesh::~Mesh() {

}

inline ModulesList Mesh::GetType() {
	return ModulesList::MeshType;
}

void Mesh::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

bool Mesh::Create(std::string linkToFBX) {
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

	if (mesh->HasPositions()) {
		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

			Geometry::_vertex[it] = mesh->mVertices[it / 3].x;
			Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
			Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;

			if (mesh->HasVertexColors(0)) {
				aiColor4D color = mesh->mColors[0][it / 3];
				//Mesh::_vertexColors->push_back(mesh->mColors());
			}
			else
			{
				Mesh::_vertexColors->push_back(0.0f);
				Mesh::_vertexColors->push_back(0.0f);
				Mesh::_vertexColors->push_back(1.0f);
			}
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

	//Material* mat = (Material*)Mesh::GetSubModuleByType(MaterialType).get();
	//if (mat != nullptr) {
	//	mat->LoadTextureCoord(*s,0);
	//	mat->LoadMaterial(*s, 0);
	//}


	Geometry::_isIndexed = true;
	//Mesh::MakeUnique();
	//Mesh::_isShifted = true;

	Mesh::BindMesh();
	return true;
}
void Mesh::ApplyTransformation()
{

}

bool Mesh::LoadTextureCoord(std::string pathToCoords) {
	return false;
}

bool Mesh::LoadTextureCoord(const aiScene& scene, unsigned int matIndex) {
	//TODO: Check if fbx
	aiMesh* mesh = scene.mMeshes[0];
	if (!mesh->HasTextureCoords(0))
		return false;

	Mesh::_texCoords->clear();
	//Material::_texCoords.get()->resize(mesh->mNumVertices * 2);

	aiMaterial* material = scene.mMaterials[matIndex];

	aiString path;
	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
		Mesh::_material->_diffuse._texturePath = path.C_Str();
	}

	for (std::uint32_t it = 0; it < mesh->mNumVertices * 2; it++) {
		Mesh::_texCoords->push_back(mesh->mTextureCoords[0][it].x);
		Mesh::_texCoords->push_back(mesh->mTextureCoords[0][it].y);
	}
}

GLfloat vert[] = {
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat col[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

bool Mesh::BindMesh() {
	if (Mesh::_vertexVbo != 0)
		glDeleteBuffers(1, &_vertexVbo);

	if (Mesh::_colorsVbo != 0)
		glDeleteBuffers(1, &_colorsVbo);

	if (Mesh::_vao != 0)
		glDeleteBuffers(1, &_vao);

	Mesh::_vertexVbo = 0;
	glGenBuffers(1, &_vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexCount * 3 * sizeof(float), Mesh::_vertex, GL_STATIC_DRAW);

	std::cout << sizeof(Mesh::_vertexColors->size());
	std::cout << sizeof(Mesh::_vertexColors.get());

	Mesh::_colorsVbo = 0;
	glGenBuffers(1, &_colorsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::_colorsVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexColors->size() * sizeof(float), Mesh::_vertexColors->data(), GL_STATIC_DRAW);

	_vao = 0;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorsVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	return true;
}
#pragma endregion
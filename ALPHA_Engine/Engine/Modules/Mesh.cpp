#include "Mesh.h"

#pragma region Mesh Define
Mesh::Mesh() {
	_material->_parentMesh = this;
}
Mesh::~Mesh() {

}

ModulesList Mesh::GetType() {
	return ModulesList::MeshType;
}

void Mesh::SetParentObject(const Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}

bool Mesh::Create(std::string linkToFBX) {
	Mesh::_indices->clear();
	Mesh::_normals->clear();
	Mesh::_texCoords->clear();

	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	aiMesh* mesh = s->mMeshes[0];

	Mesh::_indices->resize(mesh->mNumFaces * 3);

	for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
		for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
		{
			(*Mesh::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
		}
	}


	if (mesh->HasPositions()) {
		Geometry::_vertexCount = mesh->mNumVertices;
		Geometry::_vertex = new float[Geometry::_vertexCount * 3];

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
				Mesh::_vertexColors->push_back(0.9f);
				Mesh::_vertexColors->push_back(0.9f);
				Mesh::_vertexColors->push_back(0.9f);
			}
		}
	}


	if (mesh->HasNormals()) {
		Mesh::_normals->resize(Geometry::_vertexCount * 3);

		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
			(*Mesh::_normals)[it] = mesh->mNormals[it / 3].x;
			(*Mesh::_normals)[it + 1] = mesh->mNormals[it / 3].y;
			(*Mesh::_normals)[it + 2] = mesh->mNormals[it / 3].z;
		}
	}

	if (mesh->HasTextureCoords(0)) {
		Mesh::_texCoords->resize(Geometry::_vertexCount * 2);

		for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
			(*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
			(*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
		}
	}


	//Material* mat = (Material*)Mesh::GetSubModuleByType(MaterialType).get();
	if (Mesh::_material != nullptr) {
		Mesh::_material->LoadMaterial(*s, 0);
	}


	Mesh::_isIndexed = true;
	//Mesh::MakeUnique();
	//Mesh::_isShifted = true;

	Mesh::BindMesh();
	return true;
}

void Mesh::AddPosition(float X, float Y, float Z) {
	Mesh::_position.X += X;
	Mesh::_position.Y += Y;
	Mesh::_position.Z += Z;

	Mesh::_origin.X += X;
	Mesh::_origin.Y += Y;
	Mesh::_origin.Z += Z;

	Mesh::_isShifted = true;
}
void Mesh::AddPosition(Vector3 position) {
	Mesh::_position += position;
	Mesh::_origin += position;

	Mesh::_isShifted = true;
}
void Mesh::SetPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Geometry::_position;

	Mesh::AddPosition(direction);
}
void Mesh::SetPosition(Vector3 position) {
	Vector3 direction = position - Geometry::_position;

	Mesh::AddPosition(direction);
}

void Mesh::AddOriginPosition(float X, float Y, float Z) {
	Mesh::_origin.X += X;
	Mesh::_origin.Y += Y;
	Mesh::_origin.Z += Z;
}
void Mesh::AddOriginPosition(Vector3 position) {
	Mesh::_origin += position;
}

void Mesh::SetOriginPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Mesh::_origin;

	Mesh::AddOriginPosition(direction);
}
void Mesh::SetOriginPosition(Vector3 position) {
	Vector3 direction = position - Mesh::_origin;

	Mesh::AddOriginPosition(direction);
}


void Mesh::AddRotation(float X, float Y, float Z) {
	const float radX = M_PI / 180 * X;
	const float radY = M_PI / 180 * Y;
	const float radZ = M_PI / 180 * Z;

	Mesh::_rotation.X += X;
	Mesh::_rotation.Y += Y;
	Mesh::_rotation.Z += Z;

	Mesh::_isShifted = true;
}
void Mesh::AddRotation(Vector3 rotation) {
	const float radX = M_PI / 180 * rotation.X;
	const float radY = M_PI / 180 * rotation.Y;
	const float radZ = M_PI / 180 * rotation.Z;

	Mesh::_rotation.X += rotation.X;
	Mesh::_rotation.Y += rotation.Y;
	Mesh::_rotation.Z += rotation.Z;

	Mesh::_isShifted = true;
}

void Mesh::SetRotation(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Mesh::_rotation;

	Mesh::AddRotation(direction);
}
void Mesh::SetRotation(Vector3 rotation) {
	Vector3 direction = rotation - Mesh::_rotation;

	Mesh::AddRotation(direction);
}


void Mesh::SetScale(float X, float Y, float Z) {
	Mesh::_scale.X = X;
	Mesh::_scale.Y = Y;
	Mesh::_scale.Z = Z;

	Mesh::_isShifted = true;
}
void Mesh::SetScale(Vector3 scale) {
	Mesh::_scale.X = scale.X;
	Mesh::_scale.Y = scale.Y;
	Mesh::_scale.Z = scale.Z;

	Mesh::_isShifted = true;
}

void Mesh::ApplyTransformation()
{
	glm::mat4x4 rotMat(1.0f);

	const float radX = M_PI / 180 * Mesh::_rotation.X;
	const float radY = M_PI / 180 * Mesh::_rotation.Y;
	const float radZ = M_PI / 180 * Mesh::_rotation.Z;

	rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
	rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
	rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4x4 transMat(1.0f);
	transMat = glm::translate(glm::vec3(Mesh::_position.X, Mesh::_position.Y, Mesh::_position.Z));

	glm::mat4x4 scaleMat(1.0f);
	scaleMat = glm::scale(scaleMat, glm::vec3(Mesh::_scale.X, Mesh::_scale.Y, Mesh::_scale.Z));

	//Mesh::_transformMatrix = rotMat * scaleMat * transMat;
	Mesh::_transformMatrix = transMat * rotMat * scaleMat;
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

bool Mesh::BindMesh() {
	if (Mesh::_vertexVbo != 0)
		glDeleteBuffers(1, &_vertexVbo);

	if (Mesh::_colorsVbo != 0)
		glDeleteBuffers(1, &_colorsVbo);

	if (Mesh::_normalsVbo != 0)
		glDeleteBuffers(1, &_normalsVbo);

	if (Mesh::_texCoordsVbo != 0) {
		glDeleteBuffers(1, &_texCoordsVbo);
	}

	if (Mesh::_vao != 0)
		glDeleteBuffers(1, &_vao);


	glGenBuffers(1, &_vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexCount * 3 * sizeof(float), Mesh::_vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &_colorsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::_colorsVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexColors->size() * sizeof(float), Mesh::_vertexColors->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_normalsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::_normalsVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_normals->size() * sizeof(float), Mesh::_normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_texCoordsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::_texCoordsVbo);
	glBufferData(GL_ARRAY_BUFFER, Mesh::_texCoords->size() * sizeof(float), Mesh::_texCoords->data(), GL_STATIC_DRAW);

	_vao = 0;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorsVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsVbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVbo);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	return true;
}
void Mesh::ApplyMeshSettings(std::shared_ptr<Camera> camera)
{
	Mesh::_material->ApplyMaterialSettings(camera);

	glm::mat4x4 modelMat = glm::translate(glm::vec3(0, 0, 0));
	Mesh::_material->_shader->SetValue(ShadersType::VertexShader, "model_matrix", &_transformMatrix);
}
#pragma endregion
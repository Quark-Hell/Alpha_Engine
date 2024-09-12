#include "Mesh.h"
#include "Object.h"

#pragma region Mesh Define
Mesh::Mesh() {
	_material->_parentMesh = this;

	_scale = Vector3(0,0,0);
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
	Mesh::_vertex->clear();
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
		Geometry::_vertex->resize(mesh->mNumVertices * 3);

		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

			(*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
			(*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
			(*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;

			//if (mesh->HasVertexColors(0)) {
			//	aiColor4D color = mesh->mColors[0][it / 3];
			//	//Mesh::_vertexColors->push_back(mesh->mColors());
			//}
			//else
			//{
			//	Mesh::_vertexColors->push_back(0.9f);
			//	Mesh::_vertexColors->push_back(0.9f);
			//	Mesh::_vertexColors->push_back(0.9f);
			//}
		}
	}


	if (mesh->HasNormals()) {
		Mesh::_normals->resize(Geometry::_vertex->size());

		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
			(*Mesh::_normals)[it] = mesh->mNormals[it / 3].x;
			(*Mesh::_normals)[it + 1] = mesh->mNormals[it / 3].y;
			(*Mesh::_normals)[it + 2] = mesh->mNormals[it / 3].z;
		}
	}

	if (mesh->HasTextureCoords(0)) {
		Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

		for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
			(*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
			(*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
		}
	}


	Mesh::_isIndexed = true;
	Mesh::_isShifted = true;

	Mesh::BindMesh();
	return true;
}

bool Mesh::Create(std::string linkToFBX, bool initIndices, bool initVertex, bool initNormals, bool initTexCoord, bool initMaterial)
{
	Mesh::_vertex->clear();
	Mesh::_indices->clear();
	Mesh::_normals->clear();
	Mesh::_texCoords->clear();

	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s;
	aiMesh* mesh;

	if (initIndices) {
		s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		mesh = s->mMeshes[0];

		Geometry::_indices->resize(mesh->mNumFaces * 3);

		for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
			for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
			{
				(*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
			}
		}

		Geometry::_isIndexed = true;
	}
	else
	{
		s = importer.ReadFile(path, aiProcess_Triangulate);
		mesh = s->mMeshes[0];
		Geometry::_isIndexed = false;
	}

	if (mesh->HasPositions() && initVertex) {
		Geometry::_vertex->resize(mesh->mNumVertices * 3);
		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

			(*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
			(*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
			(*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
		}
	}


	if (mesh->HasNormals() && initNormals) {
		Geometry::_normals->resize(Geometry::_vertex->size());

		for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

			(*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
			(*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
			(*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
		}
	}

	if (mesh->HasTextureCoords(0) && initTexCoord) {
		Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

		for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
			(*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
			(*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
		}
	}


	Mesh::_isIndexed = true;
	Mesh::_isShifted = true;

	Mesh::BindMesh();
	return true;
}

bool Mesh::InsertVertex(Vector3 vertex, unsigned int pos, bool expand)
{
	if (pos >= Geometry::_vertex->size() / 3 && expand == false)
		return false;
	
	else if (pos >= Geometry::_vertex->size() / 3 && expand == true) {
		Geometry::_vertex->resize((pos + 1) * 3);
	
		(*Geometry::_vertex)[pos * 3] = vertex.X;
		(*Geometry::_vertex)[pos * 3 + 1] = vertex.Y;
		(*Geometry::_vertex)[pos * 3 + 2] = vertex.Z;

	
		Mesh::BindMesh();
	}
	else
	{
		(*Geometry::_vertex)[pos * 3] = vertex.X;
		(*Geometry::_vertex)[pos * 3 + 1] = vertex.Y;
		(*Geometry::_vertex)[pos * 3 + 2] = vertex.Z;
	
		Mesh::BindMesh();
	}
	return true;
}

bool Mesh::LoadTextureCoord(std::string pathToCoords) {
	return false;
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

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	if (Mesh::_vertex != nullptr) {
		glGenBuffers(1, &_vertexVbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, Mesh::_vertex->size() * sizeof(float), Mesh::_vertex->data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	if (Mesh::_normals->data() != nullptr) {
		glGenBuffers(1, &_normalsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh::_normalsVbo);
		glBufferData(GL_ARRAY_BUFFER, Mesh::_normals->size() * sizeof(float), Mesh::_normals->data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _normalsVbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	if (Mesh::_vertexColors->data() != nullptr) {
		glGenBuffers(1, &_colorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh::_colorsVbo);
		glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexColors->size() * sizeof(float), Mesh::_vertexColors->data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, _colorsVbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	if (Mesh::_texCoords->data() != nullptr) {

		glGenBuffers(1, &_texCoordsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh::_texCoordsVbo);
		glBufferData(GL_ARRAY_BUFFER, Mesh::_texCoords->size() * sizeof(float), Mesh::_texCoords->data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVbo);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	return true;
}

void Mesh::ApplyTransformation()
{
	Vector4 parentRotation;
	Vector3 parentPosition;
	Vector3 parentScale;
	Vector3 parentOrigin;

	if (ParentObject != nullptr) {
		parentRotation = ParentObject->GetRotation();
		parentPosition = ParentObject->GetPosition();
		parentScale = ParentObject->GetScale();
		parentOrigin = ParentObject->GetOriginPosition();
	}

	glm::mat4x4 parentRotMat(1.0f);

	const float parentRadX = M_PI / 180 * parentRotation.X;
	const float parentRadY = M_PI / 180 * parentRotation.Y;
	const float parentRadZ = M_PI / 180 * parentRotation.Z;

	parentRotMat = glm::rotate(parentRotMat, parentRadX, glm::vec3(1.0f, 0.0f, 0.0f));
	parentRotMat = glm::rotate(parentRotMat, parentRadY, glm::vec3(0.0f, 1.0f, 0.0f));
	parentRotMat = glm::rotate(parentRotMat, parentRadZ, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4x4 childRotMat(1.0f);

	const float childRadX = M_PI / 180 * Mesh::_rotation.X;
	const float childRadY = M_PI / 180 * Mesh::_rotation.Y;
	const float childRadZ = M_PI / 180 * Mesh::_rotation.Z;

	childRotMat = glm::rotate(childRotMat, childRadX, glm::vec3(1.0f, 0.0f, 0.0f));
	childRotMat = glm::rotate(childRotMat, childRadY, glm::vec3(0.0f, 1.0f, 0.0f));
	childRotMat = glm::rotate(childRotMat, childRadZ, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4x4 transMat(1.0f);
	transMat = glm::translate(glm::vec3(
		Mesh::_position.X + parentPosition.X,
		Mesh::_position.Y + parentPosition.Y,
		Mesh::_position.Z + parentPosition.Z));

	glm::mat4x4 scaleMat(1.0f);
	scaleMat = glm::scale(scaleMat, glm::vec3(
		Mesh::_scale.X + parentScale.X,
		Mesh::_scale.Y + parentScale.Y,
		Mesh::_scale.Z + parentScale.Z));


	glm::mat4x4 parentOriginMat(1.0f);
	parentOriginMat = glm::translate(parentOriginMat, glm::vec3(
		-parentOrigin.X,
		-parentOrigin.Y,
		-parentOrigin.Z));

	glm::mat4x4 backParentOriginMat(1.0f);
	backParentOriginMat = glm::translate(backParentOriginMat, glm::vec3(
		parentOrigin.X,
		parentOrigin.Y,
		parentOrigin.Z));


	glm::mat4x4 childOriginMat(1.0f);
	childOriginMat = glm::translate(childOriginMat, glm::vec3(
		-Mesh::_origin.X,
		-Mesh::_origin.Y,
		-Mesh::_origin.Z));

	glm::mat4x4 backChildOriginMat(1.0f);
	backParentOriginMat = glm::translate(backParentOriginMat, glm::vec3(
		Mesh::_origin.X,
		Mesh::_origin.Y,
		Mesh::_origin.Z));

	glm::mat4x4 rotMat = backParentOriginMat * parentRotMat * parentOriginMat * backChildOriginMat * childRotMat * childOriginMat;

	Mesh::_transformMatrix = transMat * rotMat * scaleMat;
}

#pragma endregion
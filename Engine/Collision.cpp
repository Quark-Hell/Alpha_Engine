#include "Collision.h"
#include <unordered_map>
#include <chrono>


inline bool Collision::CreateCollision(std::string link) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + link.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
	aiMesh* mesh = s->mMeshes[0];

	GeneralCollider->Points.clear();
	GeneralCollider->Normals.clear();

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

		GeneralCollider->Points.push_back(point);
		GeneralCollider->Normals.push_back(normal);
	}

	SeparateCollision();

	return true;
}

/*
inline bool Collision::IsNeighbor(Triangle* current, Triangle* neighbor) {
	//current Vert 1
	if (current->Vert1 == neighbor->Vert1) {
		return true;
	}
	else if (current->Vert1 == neighbor->Vert2)
	{
		return true;
	}
	else if (current->Vert1 == neighbor->Vert3)
	{
		return true;
	}
	//current Vert 2
	else if (current->Vert2 == neighbor->Vert1)
	{
		return true;
	}
	else if (current->Vert2 == neighbor->Vert2)
	{
		return true;
	}
	else if (current->Vert2 == neighbor->Vert3)
	{
		return true;
	}
	//current Vert 3
	else if (current->Vert3 == neighbor->Vert1)
	{
		return true;
	}
	else if (current->Vert3 == neighbor->Vert2)
	{
		return true;
	}
	else if (current->Vert3 == neighbor->Vert3)
	{
		return true;
	}
	return false;
}

inline bool Collision::SeparateCollision() {
	Triangle currentTriangle;
	Triangle neighborTriangle;

	size_t countOfPrimitives;
	while (Collision::GeneralCollider->Points.size() != 0)
	{
		Collision::PrimitivesCollider.push_back(new Collider);
		countOfPrimitives = Collision::PrimitivesCollider.size() - 1;

		currentTriangle.Vert1 = Collision::GeneralCollider->Points[0];
		currentTriangle.Vert2 = Collision::GeneralCollider->Points[1];
		currentTriangle.Vert3 = Collision::GeneralCollider->Points[2];

		Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(currentTriangle.Vert1);
		Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(currentTriangle.Vert2);
		Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(currentTriangle.Vert3);

		//Erease current triangle from general buffer
		Collision::GeneralCollider->Points.erase(Collision::GeneralCollider->Points.begin(), Collision::GeneralCollider->Points.begin() + 3);

		size_t it = 3;
		do
		{
			for (size_t jt = 0; jt < Collision::GeneralCollider->Points.size(); jt += 3)
			{
				//Definition neighbor triangle
				neighborTriangle.Vert1 = Collision::GeneralCollider->Points[jt];
				neighborTriangle.Vert2 = Collision::GeneralCollider->Points[jt + 1];
				neighborTriangle.Vert3 = Collision::GeneralCollider->Points[jt + 2];

				//Check is neigbor triangle really neighbor for current triangle
				if (IsNeighbor(&currentTriangle, &neighborTriangle)) {
					Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(neighborTriangle.Vert1);
					Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(neighborTriangle.Vert2);
					Collision::PrimitivesCollider[countOfPrimitives]->Points.push_back(neighborTriangle.Vert3);

					//Erease current triangle from general buffer
					Collision::GeneralCollider->Points.erase(Collision::GeneralCollider->Points.begin() + jt, Collision::GeneralCollider->Points.begin() + jt + 3);

					currentTriangle.Vert1 = neighborTriangle.Vert1;
					currentTriangle.Vert2 = neighborTriangle.Vert2;
					currentTriangle.Vert3 = neighborTriangle.Vert3;

					it += 3;
					jt = -3;
				}
			}

			it -= 3;

			if (it != 0) {
				currentTriangle.Vert1 = Collision::PrimitivesCollider[countOfPrimitives]->Points[it - 3];
				currentTriangle.Vert2 = Collision::PrimitivesCollider[countOfPrimitives]->Points[it - 2];
				currentTriangle.Vert3 = Collision::PrimitivesCollider[countOfPrimitives]->Points[it - 1];
			}

		} while (it != 0);
	}

	return true;
}
*/


inline void Collision::SwapToEndAndDelete(unsigned int from, std::vector<int> *vector) {
	unsigned int temp = (*vector)[vector->size() - 1];
	(*vector)[vector->size() - 1] = (*vector)[from];
	(*vector)[from] = temp;
	vector->pop_back();
}

inline void Collision::InsertTriangle(unsigned int PrimitiveObjectID, 
	unsigned int TriangleID, 
	unsigned int TriangleNum,
	std::vector<int>* AdjacentTriangles) {

	Collision::PrimitivesCollider[PrimitiveObjectID]->Points.push_back(GeneralCollider->Points[TriangleID * 3]);
	Collision::PrimitivesCollider[PrimitiveObjectID]->Points.push_back(GeneralCollider->Points[TriangleID * 3 + 1]);
	Collision::PrimitivesCollider[PrimitiveObjectID]->Points.push_back(GeneralCollider->Points[TriangleID * 3 + 2]);

	//Collision::SwapToEndAndDelete(TriangleNum, AdjacentTriangles);
	AdjacentTriangles->erase(AdjacentTriangles->begin() + TriangleNum);
}

inline std::vector<int*> ItBuffer = {};
inline void Collision::SearchFrom(unsigned int from, std::vector<int>* vector) {
	int it = vector->size() - 1;
	ItBuffer.push_back(&it);
	for (; it >= 0; it--)
	{
		if (from == (*vector)[it]) {
			unsigned int triangleID;
			if (it % 2 == 0) {
				triangleID = (*vector)[it + 1];
			}
			else
			{
				triangleID = (*vector)[it - 1];
			}

			//Collision::SwapToEndAndDelete(it, vector);
			vector->erase(vector->begin() + it);
			Collision::InsertTriangle(Collision::PrimitivesCollider.size() - 1, (*vector)[it - 1], it - 1, vector);

			for (size_t jt = 0; jt < ItBuffer.size() - 1; jt++)
			{
				*ItBuffer[jt] -= 2;
			}
			it--;

			Collision::SearchFrom(triangleID, vector);
		}
	}
	ItBuffer.pop_back();
}


inline bool Collision::SeparateCollision() {
	// Get starting timepoint
	auto start = std::chrono::high_resolution_clock::now();


	struct EdgeInfo
	{
		Vector3 *Point1;
		Vector3 *Point2;
		unsigned int TriangleID;
	};

	std::unordered_map<std::string, EdgeInfo> edgeMap;
	std::string hash;

	// -------------------------------------------------------------------------
	/*
	Adjacent triangles are stored in pairs.
	Example:
	We have {0,1,1,2,6,5} vector
	So:
	0 and 1 - Adjacent
	1 and 2 - Adjacent
	6 and 5 - Adjacent
	*/
	std::vector<int> adjacentTriangles;
	// -------------------------------------------------------------------------

	//Create unique egde list
	for (size_t it = 0; it <= GeneralCollider->Points.size() - 1; it++)
	{
		EdgeInfo edge;
		//chesh if last point of triangle
		if ((it + 1) % 3 == 0) {
			edge.Point1 = &GeneralCollider->Points[it];
			edge.Point2 = &GeneralCollider->Points[it - 2];
		}
		else
		{
			edge.Point1 = &GeneralCollider->Points[it];
			edge.Point2 = &GeneralCollider->Points[it + 1];
		}
		edge.TriangleID = it / 3;


		const int arr_len = 6;
		float edgeArr[arr_len];

		//create same direction line
		if ((edge.Point1->X > edge.Point2->X) || (edge.Point1->X == edge.Point2->X && edge.Point1->Y > edge.Point2->Y) || (edge.Point1->X == edge.Point2->X && edge.Point1->Y == edge.Point2->Y && edge.Point1->Z > edge.Point2->Z)) {
			edgeArr[0] = { edge.Point1->X };
			edgeArr[1] = { edge.Point1->Y };
			edgeArr[2] = { edge.Point1->Z };
			edgeArr[3] = { edge.Point2->X };
			edgeArr[4] = { edge.Point2->Y };
			edgeArr[5] = { edge.Point2->Z };
		}
		else
		{
			edgeArr[0] = { edge.Point2->X };
			edgeArr[1] = { edge.Point2->Y };
			edgeArr[2] = { edge.Point2->Z };
			edgeArr[3] = { edge.Point1->X };
			edgeArr[4] = { edge.Point1->Y };
			edgeArr[5] = { edge.Point1->Z };
		}

		unsigned int sizeBeforeInsert = edgeMap.size();

		//create hash
		hash.resize(arr_len * sizeof(float));
		memcpy((char*)hash.data(), edgeArr, arr_len * sizeof(float));

		//insert hash
		std::pair<std::string, EdgeInfo> p(hash, edge);
		edgeMap.insert(p);

		//chech if hash map not changed size after insert hash
		//is not changed => found same edges => found adjacent triangles
		if (sizeBeforeInsert == edgeMap.size()) {
			adjacentTriangles.push_back(edgeMap.find(hash)->second.TriangleID);
			adjacentTriangles.push_back(edge.TriangleID);
		}
	}
	/*
	size_t countOfPrimitives;

  	while (adjacentTriangles.size() != 0)
	{
		Collision::PrimitivesCollider.push_back(new Collider);
		countOfPrimitives = Collision::PrimitivesCollider.size() - 1;

		unsigned int lastTriangleID = adjacentTriangles[adjacentTriangles.size() - 1];

		Collision::InsertTriangle(countOfPrimitives, adjacentTriangles[adjacentTriangles.size() - 1], adjacentTriangles.size() - 1, &adjacentTriangles);
		Collision::InsertTriangle(countOfPrimitives, adjacentTriangles[adjacentTriangles.size() - 1], adjacentTriangles.size() - 1, &adjacentTriangles);

		Collision::SearchFrom(lastTriangleID, &adjacentTriangles);
	}
	*/

	// Get ending timepoint
			auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast	<std::chrono::milliseconds>(stop - start);

	std::cout << "Time taken by function: "
		<< duration.count() << " milliseconds" << std::endl;

	return true;
}

inline bool Collision::CreateConvexFromÑoncave(std::string link) {

}
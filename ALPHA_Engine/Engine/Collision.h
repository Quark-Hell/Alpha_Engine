#pragma once
#include "Basical_Type.h"
#include "Alghoritms.h"
#include "Mesh.h"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Simplex
{
private:
	std::array<Vector3, 4> _points;
	unsigned _size;

public:
	Simplex(std::array<Vector3, 4> points = { Vector3{0,0,0}, Vector3{0,0,0}, Vector3{0,0,0}, Vector3{0,0,0} }, unsigned size = 0);

	Simplex& operator=(std::initializer_list<Vector3> list) {
		for (auto v = list.begin(); v != list.end(); v++) {
			_points[std::distance(list.begin(), v)] = *v;
		}
		_size = list.size();

		return *this;
	}

	Vector3& operator[](unsigned i) { return _points[i]; }

	void PushFront(Vector3 point);
	unsigned GetSize();

	auto begin() const { return _points.begin(); }
	auto end()   const { return _points.end() - (4 - _size); }

	static inline bool NextSimplex(Simplex& points, Vector3& direction);
	static inline bool SameDirection(const Vector3& direction, const Vector3& ao);

	static inline bool Line(Simplex& points, Vector3& direction);
	static inline bool Triangle(Simplex& points, Vector3& direction);
	static inline bool Tetrahedron(Simplex& points, Vector3& direction);
};

class Collider : public Mesh {
public:
	bool CreateCollider(std::string link);

	bool SeparateCollision();
	bool CreateConvexFrom—oncave(std::string link);

private:
	friend class Collision;
	friend class Graph;
};

class Collision{
public:
	static inline Vector3 Support(Collider* colliderA, Collider* colliderB, Vector3 direction);
	static inline bool GJK(Collider* colliderA, Collider* colliderB);

	
};


#pragma once
#include "Modules/Geometry.h"

class MeshCollider;
class CollisionInfo;

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

class Collision{
public:
	static void CollisionLoop();

	static inline unsigned int GJKaccurate = 100;
	static inline unsigned int EPAaccurate = 100;

private:
	//static bool BoxToBox(BoxCollider& colliderA, BoxCollider& colliderB);
	//static bool SphereToSphere(Geometry& colliderA, Geometry& colliderB);
	//static bool SphereToBox(Geometry& colliderA, Geometry& colliderB);

	static Vector3 Support(Geometry& colliderA, Geometry& colliderB, Vector3 direction);
	static bool GJK(Geometry& colliderA, Geometry& colliderB, CollisionInfo& colPoints);
	static CollisionInfo EPA(Simplex& simplex, Geometry& colliderA, Geometry& ColliderB);

	static std::pair<std::vector<Vector4>, size_t> GetFaceNormals(std::vector<Vector3>& polytope, std::vector<size_t>& faces);
	static void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces,size_t a,size_t b);

	static std::shared_ptr<std::vector<float>> GetContactPoints(Geometry& geometry,Vector3 moveVector);
};


#pragma once
#include "Modules/Geometry.h"

class Simplex
{
public:
	std::array<std::pair<Vector3, Vector3>, 4> _points;
	unsigned _size;

public:
	std::pair<Vector3, Vector3>& operator[](unsigned i) { return _points[i]; }

	auto begin() const { return _points.begin(); }
	auto end()   const { return _points.end(); }

	static inline bool SameDirection(const Vector3& direction, const Vector3& ao);

	static inline void UpdateSimplex3(Simplex& simplex, int& simp_dim, Vector3& search_dir);
	static inline bool UpdateSimplex4(Simplex& simplex, int& simp_dim, Vector3& search_dir);
};

class CollisionInfo {
public:
	Vector3 Normal;
	float PenetrationDepth;
	bool HasCollision;

	//std::shared_ptr<std::vector<float>> CollisionPoints;
};

class Collider : public Geometry {
public:
	Collider();
	~Collider();

	bool CreateConvexFrom—oncave(std::string link);
	CollisionInfo GetCollisionInfo();

private:
	friend class Collision;

	CollisionInfo collisionInfo;
};

static class Collision{
public:
	static inline void CollisionLoop();

	static inline unsigned int GJKaccurate = 100;
	static inline unsigned int EPAaccurate = 256;

private:
	static inline Vector3 Support(Collider& colliderA, Collider& colliderB, Vector3 direction);
	static inline bool GJK(Collider& colliderA, Collider& colliderB, Simplex& simplex);

	static inline CollisionInfo EPA(Simplex& simplex, Collider& colliderA, Collider& ColliderB, Vector3 movVector);

	static inline std::pair<std::vector<Vector4>, size_t> GetFaceNormals(std::vector<Vector3>& polytope, std::vector<size_t>& faces);
	static inline void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b);

	static inline void ResolveCollision(Collider& colliderA, Collider& ColliderB);
};


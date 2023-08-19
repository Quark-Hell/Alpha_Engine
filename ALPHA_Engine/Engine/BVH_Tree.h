#pragma once

#include "Basical_Type.h"
#include "Object.h"
#include "AABB.h"

class Leaf;

class BVH_Tree {
public:
	BVH_Tree();
	~BVH_Tree();

	Vector3 GetPosition();
	AABB AABBvolume;
};

class Node : public BVH_Tree {
public:
	std::vector<std::shared_ptr<Leaf>> leavesPtr;


public:
	Node(size_t reserveCount = 8);
	virtual ~Node();
};

class Leaf : public BVH_Tree {
public:
	std::vector<Object*> objectsPtr;

public:
	Leaf(size_t reserveCount = 8);
	virtual ~Leaf();
};
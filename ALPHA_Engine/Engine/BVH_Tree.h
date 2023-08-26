#pragma once

#include "Basical_Type.h"
#include "Object.h"
#include "AABB.h"

class Leaf;

class BVH_Tree {
public:
	BVH_Tree();
	~BVH_Tree();

	AABB AABBvolume;
};

class Node : public BVH_Tree {
private:
	const bool _isNodesStorage = true;

	std::vector<std::shared_ptr<Leaf>> _leavesPtr;
	std::vector<std::shared_ptr<Node>> _nodesPtr;

public:
	void Insert(std::shared_ptr<Leaf> leaf, size_t pos);
	void Insert(std::shared_ptr<Node> node, size_t pos);

	void Insert(Leaf* leaf, size_t pos);
	void Insert(Node* node, size_t pos);

	void PushBack(std::shared_ptr<Leaf> leaf);
	void PushBack(std::shared_ptr<Node> node);

	void PushBack(Leaf* leaf);
	void PushBack(Node* node);

	size_t GetSize();
	size_t GetCapacity();

	void Get(std::shared_ptr<Leaf>* buffer, size_t index);
	void Get(Leaf** buffer, size_t index);

	void Get(std::shared_ptr<Node>* buffer, size_t index);
	void Get(Node** buffer, size_t index);

public:
	Node(bool isNodesStorage = false, size_t reserveCount = 8);
	virtual ~Node();
};

class Leaf : public BVH_Tree {
public:
	std::vector<std::shared_ptr<Collider>> _collidersPtr;

public:
	Leaf(size_t reserveCount = 8);
	virtual ~Leaf();

	void Insert(std::shared_ptr<Collider> collider, size_t pos);

	void PushBack(std::shared_ptr<Collider> collider);
	void PushBack(Collider* collider);

	size_t GetSize();
	size_t GetCapacity();

	void Get(std::shared_ptr<Collider>* buffer, size_t index);
	void Get(Collider** buffer, size_t index);
};
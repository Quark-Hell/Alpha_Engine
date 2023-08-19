#include "BVH_Tree.h"

BVH_Tree::BVH_Tree() {
	BVH_Tree::AABBvolume = AABB{ 0,1,0,1,0,1 };
}
BVH_Tree::~BVH_Tree() {

}

Node::Node(size_t reserveCount) {
	leavesPtr.reserve(reserveCount);
}
Node::~Node() {

}

Leaf::Leaf(size_t reserveCount) {
	objectsPtr.reserve(reserveCount);
}
Leaf::~Leaf() {

}

Vector3 BVH_Tree::GetPosition() {
	return { BVH_Tree::AABBvolume.MinX, BVH_Tree::AABBvolume.MinY, BVH_Tree::AABBvolume.MinZ};
}
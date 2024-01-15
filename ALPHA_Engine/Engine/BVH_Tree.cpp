#include "BVH_Tree.h"

BVH_Tree::BVH_Tree() {

}
BVH_Tree::~BVH_Tree() {

}

Node::Node(bool isNodesStorage, size_t reserveCount) : _isNodesStorage(isNodesStorage) {
	if (Node::_isNodesStorage) {
		_nodesPtr.reserve(reserveCount);
		return;
	}
	_leavesPtr.reserve(reserveCount);
}
Node::~Node() {

}

void Node::Insert(std::shared_ptr<Leaf> leaf, size_t pos) {
	if (Node::_isNodesStorage)
		return;

	Node::_leavesPtr.insert(Node::_leavesPtr.begin() + pos, leaf);
}
void Node::Insert(std::shared_ptr<Node> node, size_t pos) {
	if (!Node::_isNodesStorage)
		return;

	Node::_nodesPtr.insert(Node::_nodesPtr.begin() + pos, node);
}
void Node::Insert(Leaf* leaf, size_t pos) {
	if (Node::_isNodesStorage)
		return;

	Node::_leavesPtr.insert(Node::_leavesPtr.begin() + pos, std::shared_ptr<Leaf>(leaf));
}
void Node::Insert(Node* node, size_t pos) {
	if (!Node::_isNodesStorage)
		return;

	Node::_nodesPtr.insert(Node::_nodesPtr.begin() + pos, std::shared_ptr<Node>(node));
}

void Node::PushBack(std::shared_ptr<Leaf> leaf) {
	if (Node::_isNodesStorage)
		return;

	Node::_leavesPtr.push_back(leaf);
}
void Node::PushBack(std::shared_ptr<Node> node) {
	if (!Node::_isNodesStorage)
		return;

	Node::_nodesPtr.push_back(node);
}
void Node::PushBack(Leaf* leaf) {
	if (Node::_isNodesStorage)
		return;

	Node::_leavesPtr.push_back(std::shared_ptr<Leaf>(leaf));
}
void Node::PushBack(Node* node) {
	if (!Node::_isNodesStorage)
		return;

	Node::_nodesPtr.push_back(std::shared_ptr<Node>(node));
}

size_t Node::GetSize() {
	if (Node::_isNodesStorage)
		return Node::_nodesPtr.size();

	return Node::_leavesPtr.size();
}
size_t Node::GetCapacity() {
	if (Node::_isNodesStorage)
		return Node::_nodesPtr.capacity();

	return Node::_leavesPtr.capacity();
}

void Node::Get(std::shared_ptr<Node>* buffer, size_t index) {
	if (Node::_isNodesStorage)
		*buffer = Node::_nodesPtr[index];
}
void Node::Get(Node** buffer, size_t index) {
	if (Node::_isNodesStorage)
		*buffer = Node::_nodesPtr[index].get();
}

void Node::Get(std::shared_ptr<Leaf>* buffer, size_t index) {
	if (!Node::_isNodesStorage)
		*buffer = Node::_leavesPtr[index];
}
void Node::Get(Leaf** buffer, size_t index) {
	if (!Node::_isNodesStorage)
		*buffer = Node::_leavesPtr[index].get();
}


Leaf::Leaf(size_t reserveCount) {
	_collidersPtr.reserve(reserveCount);
}
Leaf::~Leaf() {

}

void Leaf::Insert(std::shared_ptr<Collider> collider, size_t pos) {
	Leaf::_collidersPtr.insert(Leaf::_collidersPtr.begin() + pos, collider);
}

void Leaf::PushBack(std::shared_ptr<Collider> collider) {
	Leaf::_collidersPtr.push_back(collider);
}
void Leaf::PushBack(Collider* collider) {
	Leaf::_collidersPtr.push_back(std::shared_ptr<Collider>(collider));
}

size_t Leaf::GetSize() {
	return Leaf::_collidersPtr.size();
}
size_t Leaf::GetCapacity() {
	return Leaf::_collidersPtr.capacity();
}
void Leaf::Get(std::shared_ptr<Collider>* buffer, size_t index) {
	*buffer = Leaf::_collidersPtr[index];
}
void Leaf::Get(Collider** buffer, size_t index) {
	*buffer = Leaf::_collidersPtr[index].get();
}
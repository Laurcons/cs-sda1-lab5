#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r): r(r) {
	head = nullptr;
}


bool SortedSet::add(TComp elem) {
	// search for the elem
	Node* c = head;
	Node* prev = nullptr;
	while (c != nullptr) {
		if (c->val == elem)
			return false;
		prev = c;
		if (r(elem, c->val))
			c = c->left;
		else c = c->right;
	}
	// create the node
	Node* newNode = new Node{ elem, nullptr, nullptr };
	// attach it
	if (head == nullptr)
		head = newNode;
	else {
		if (r(elem, prev->val))
			prev->left = newNode;
		else prev->right = newNode;
	}
	count++;
	return true;
}

SortedSet::Node* SortedSet::maxLeft(Node* start) const {
	Node* c = start->left;
	Node* prev = start;
	while (c->right != nullptr)
		prev = c,
		c = c->right;
	return prev;
}

bool SortedSet::remove(TComp elem) {
	// search for the elem
	Node* c = head;
	Node* prev = nullptr;
	while (c != nullptr) {
		if (c->val == elem)
			break;
		prev = c;
		if (r(elem, c->val))
			c = c->left;
		else
			c = c->right;
	}
	if (c == nullptr)
		return false;
	count--;
	bool isLeft = prev != nullptr && r(c->val, prev->val);
	// if the node has no children
	// if the two pointers are equal, surely they are nullptr, right?
	if (c->left == c->right) {
		// just remove the node and fix the parent's reference
		delete c;
		if (prev == nullptr)
			head = nullptr;
		else {
			if (isLeft)
				prev->left = nullptr;
			else prev->right = nullptr;
		}
		return true;
	}
	// if the node has only right child
	if (c->left == nullptr) {
		if (prev == nullptr) {
			head = c->right;
			delete c;
		}
		else {
			if (isLeft) {
				prev->left = c->right;
			}
			else {
				prev->right = c->right;
			}
			delete c;
		}
		return true;
	}
	// if the node has only left child
	if (c->right == nullptr) {
		if (prev == nullptr) {
			head = c->left;
			delete c;
		}
		else {
			if (isLeft) {
				prev->left = c->left;
			}
			else {
				prev->right = c->left;
			}
			delete c;
		}
		return true;
	}
	// if the node has both children
	auto ml = maxLeft(c);
	c->val = ml->right->val;
	delete ml->right;
	ml->right = nullptr;
	return true;
}


bool SortedSet::search(TComp elem) const {
	// search for the elem
	Node* c = head;
	Node* prev = nullptr;
	while (c != nullptr) {
		if (c->val == elem)
			return true;
		prev = c;
		if (r(elem, c->val))
			c = c->left;
		else
			c = c->right;
	}
	return false;
}

int SortedSet::size() const {
	return count;
}

bool SortedSet::isEmpty() const {
	return count == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

SortedSet::~SortedSet() {
	Node* node = head;
	Node* up = nullptr;

	while (node != nullptr) {
		if (node->left != nullptr) {
			Node* left = node->left;
			node->left = up;
			up = node;
			node = left;
		}
		else if (node->right != nullptr) {
			Node* right = node->right;
			node->left = up;
			node->right = nullptr;
			up = node;
			node = right;
		}
		else {
			if (up == nullptr) {
				delete node;
				node = nullptr;
			}
			while (up != nullptr) {
				delete node;
				if (up->right != nullptr) {
					node = up->right;
					up->right = nullptr;
					break;
				}
				else {
					node = up;
					up = up->left;
				}
			}
		}
	}
}



#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m)
{
	stack = nullptr;
	first();
}


void SortedSetIterator::first() {
	if (stack == nullptr)
		stack = new SortedSet::Node * [set.size()];
	len = 0;
	current = nullptr;
	SortedSet::Node* c = set.head;
	while (c != nullptr)
		stack[len++] = c,
		c = c->left;
	nextInternal();
}

void SortedSetIterator::nextInternal() {
	if (len == 0) {
		current = nullptr;
		return;
	}
	SortedSet::Node* c = stack[--len];
	current = c;
	if (c->right != nullptr) {
		c = c->right;
		while (c != nullptr) {
			stack[len++] = c;
			c = c->left;
		}
	}
}

void SortedSetIterator::next() {
	if (!valid())
		throw std::exception();
	nextInternal();
}


TElem SortedSetIterator::getCurrent()
{
	if (!valid())
		throw std::exception();
	return current->val;
}

bool SortedSetIterator::valid() const {
	return current != nullptr;
}

SortedSetIterator::~SortedSetIterator() {
	delete[] stack;
}

#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& set;
	SortedSetIterator(const SortedSet& m);

	SortedSet::Node** stack;
	int len;
	SortedSet::Node* current;

	void nextInternal();

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	~SortedSetIterator();
};


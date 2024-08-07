#pragma once
#include <stack>

#include "SortedSet.h"

//DO NOT CHANGE THIS PART
struct Stack {
	BTSNode *stack;
	int top,capacity;
};

class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	BTSNode* iterator;
	Stack array;
	void inorder(struct BTSNode *node);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	~SortedSetIterator();


};


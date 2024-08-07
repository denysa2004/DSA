#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART

class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	//SortedIteratedList<int> otherList;
	ListIterator(const SortedIteratedList& list);


    Node* it;       //iterator pentru noduri
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};



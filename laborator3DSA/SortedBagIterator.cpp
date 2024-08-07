#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->itElem=bag.head;            //complexitate Q(1)
	this->itFrecv=0;
}

TComp SortedBagIterator::getCurrent() {
	if(valid()) {
		return bag.elems[itElem].first;          //complexitate Q(1)
	}
	else throw exception();
}

bool SortedBagIterator::valid() {
   if(itElem!=-1 && itFrecv<=bag.elems[itElem].second)    //complexitate Q(1)
   	return true;

	return false;
}

void SortedBagIterator::next() {
	if(itElem != -1 && itFrecv < bag.elems[itElem].second){
		if(itFrecv == bag.elems[itElem].second - 1){
			itFrecv = 0;
			itElem = bag.next[itElem];                        //Q(1)-complexitate
		}
		else if(itFrecv < bag.elems[itElem].second){
			itFrecv ++;
		}

	}
	else{
		throw exception();
	}
}

void SortedBagIterator::first() {
	itElem=bag.head;             //primul element ,complexitate Q(1)
	itFrecv=0;
}


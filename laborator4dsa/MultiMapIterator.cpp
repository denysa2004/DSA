#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->first();                                //BC Q(1), AC Q(n) ,WC Q(n)
}

TElem MultiMapIterator::getCurrent() const{
	if(valid())
		return this->col.table[this->iterator];
	else
		throw exception();                      //Q(1)-complexitate

}

bool MultiMapIterator::valid() const {
	if(this->iterator<this->col.capacity)
		return true;
	return false;                              //Q(1)-complexitate
}

void MultiMapIterator::next() {

	if(this->iterator>=this->col.capacity)
		throw exception();                          //BC Q(1),AC Q(n),WC Q(n)
	this->iterator++;
	while(col.table[this->iterator]==NULL_TELEM)
		this->iterator++;
}

void MultiMapIterator::first() {
	this->iterator = 0;
	while(col.table[this->iterator]==NULL_TELEM)     //BC Q(1), AC Q(n) ,WC Q(n)
		this->iterator++;

}

void MultiMapIterator::changeCurrent(TKey c,TValue v) {
	if (valid()) {
		if(this->col.table[this->iterator].first!=c &&this->col.table[this->iterator].second!=v) {
			this->col.table[this->iterator].first=c;       //daca ambele sunt diferite
			this->col.table[this->iterator].second =v;
		}
		else if(this->col.table[this->iterator].first ==c &&this->col.table[this->iterator].second!=v)
			this->col.table[this->iterator].second =v;      //daca doar valoarea este diferita
		else if(this->col.table[this->iterator].first !=c &&this->col.table[this->iterator].second==v)
			this->col.table[this->iterator].first =c;     //daca doar cheia este diferita
		else if(this->col.table[this->iterator]==NULL_TELEM) {
			this->col.table[this->iterator].first=c;       //daca ambele sunt diferite
			this->col.table[this->iterator].second =v;

		}

	} else {
		throw exception();
	}
}

#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	if(list.head!=nullptr)
		it=list.head;   //initializam iteratorul cu primul element
	else{it=nullptr;}   //altfel cu nullptr
}                       //complexitate Q(1)

void ListIterator::first(){
	if(list.head!=nullptr)
		it=list.head;   //initializam iteratorul cu primul element
	else{it=nullptr;}   //altfel cu nullptr
}
                        // complexitate Q(1)


void ListIterator::next(){
    if(it == nullptr)
        throw exception();     //daca iteratorul e diferit de null pointer trecem la urmatorul,altfel exceptie
    else                       //Q(1)-complexitate
        it=it->next;
}

bool ListIterator::valid() const{
    if(it!= nullptr)           //daca iteratorul este diferit de pointerul null ,atunci returnam true,altfel false
        return true;           //Q(1)-complexitate
	return false;
}

TComp ListIterator::getCurrent() const{
    if(it!= nullptr)
        return it->data;   //daca iteratorul e diferit de pointerul null returnam nodul curent
	return NULL_TCOMP;     //Q(1)-complexitate
}



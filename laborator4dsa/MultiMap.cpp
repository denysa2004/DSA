#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <vector>
using namespace std;


MultiMap::MultiMap() {
	this->capacity=300000;
	this->length=0;
	this->table=new TElem[this->capacity];
                                                     //complexitate Q(n)
	for(int i=0;i<this->capacity;i++) {
		this->table[i]=NULL_TELEM;
	}
}


void MultiMap::add(TKey c, TValue v) {

	if( this->length / this->capacity == LOAD_FACTOR)
		this->resize_rehash();                         //complexitate Q(1)-BC Q(n)-AC Q(n)-WC
	int i, position;

	i = 0;
	position = this->HashDivisionsMethode(c, i);

	while(i < this->capacity && this->table[position] != NULL_TELEM) {
		i++;
		position = this->HashDivisionsMethode(c, i);
	}
	this->table[position].first=c;
	this->table[position].second=v;
	this->length++;
}


bool MultiMap::remove(TKey c, TValue v) {
	int i, position;                        //complexitate Q(1)-BC Q(n)-AC Q(n)-WC
	i = 0;
	position = this->HashDivisionsMethode(c, i);

	while(i < this->capacity && this->table[position] != NULL_TELEM) {
		if(this->table[position] == TElem(c, v))
		{

			this->table[position] = DELETED_TELEM;
			this->length--;
			return true;
		}
		i++;
		position = this->HashDivisionsMethode(c, i);
	}
	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values {};                       //complexitate Q(1)-BC Q(n)-AC Q(n)-WC
	int i, position;
	i = 0;
	position = this->HashDivisionsMethode(c, i);

	while(i < this->capacity && this->table[position] != NULL_TELEM) {
		if(this->table[position].first == c)
			values.push_back(this->table[position].second);
		i++;
		position = this->HashDivisionsMethode(c, i);
	}
	return values;
}


int MultiMap::size() const {
	return this->length;          //complexitate Q(1)
}


bool MultiMap::isEmpty() const {
	if(this->length==0)
		return true;          //complexitate Q(1)
	return false;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	delete[] table;            //complexitate Q(n)
}


void MultiMap::resize_rehash() {

	int oldCapacity = this->capacity;
	this->capacity = oldCapacity*2;                      //O(n^2)-complexitate
	TElem* newArray = new TElem[this->capacity];

	for(int i=0; i< this->capacity; i++)
		newArray[i] = NULL_TELEM;

	for(int j=0; j< oldCapacity; j++) {
		if(table[j] != NULL_TELEM) {

			int i, position;

			i = 0;
			position = this->HashDivisionsMethode(table[j].first, i);

			while(i < this->capacity && newArray[position] != NULL_TELEM) {
				i++;
				position = this->HashDivisionsMethode(table[j].first, i);
			}
			newArray[position].first=table[j].first;
			newArray[position].second=table[j].second;
		}
	}
	delete[] table;
	table=newArray;
}


int MultiMap::HashDivisionsMethode(TKey key, int j) const{
	int c1=3,c2=1;
	long long result=abs(key)%this->capacity+c1*j+c2*j*j;   //complexitate Q(1)
	return (int) result;
}





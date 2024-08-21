#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation1                                        //Q(1)-allgemeine Komplexitat
    this->index=0; //punem indexul la prima pozitie
}

MapIterator::MapIterator(const Map& d,int n) : map(d) {
    if (n >= 0 && n <= this->map.length) {                             //Q(1)-allgemeine complexitat
        this->index = n;
    }
}


void MapIterator::first() {
	//TODO - Implementation1
    this->index=0;   //prima pozitie         // Q(1)-allgemeine Komplexitat
}                                            // primul element din lista 


void MapIterator::next() {
	//TODO - Implementation1
    if (this->index< this->map.length)
        this->index++;                    //Q(1)-allgemeine Komplexitat
    else{                                 //sarim la pozitia urmatoare
        throw exception();}
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation1
    if (this->index< this->map.length) {                         //returnam elemntul de pe pozitia curenta
     TElem getcurrent = this->map.myArray[this->index];          //Q(1)-allgemeine Komplexitat
     return getcurrent;
    }
    else {
	throw exception();
    }
}


bool MapIterator::valid() const {
	//TODO - Implementation1
    if (this->index < this->map.length)            //Q(1)-allgemeine Komplexitat
        return true;                               //verificam daca pozitia este valida
	return false;
}

void MapIterator::nextiterator(int n) {

    if (this->index+n< this->map.length && n>0)
        this->index+=n;
    else if (this->index+n < this->map.length && this->index+n > 0 && n<0)     //Q(1)-allgemeine Komplexitat
        this->index=-n;
    else{
        throw exception();}
}



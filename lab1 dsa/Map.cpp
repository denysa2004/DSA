#include "Map.h"
#include "MapIterator.h"
#include <vector>
#include <utility>
Map::Map() {
	//TODO - Implementation1
     this->capacity=10;//initatle Speicherplatz
     this->length=0;//die Lange des Arrays      //Q(1)
     this->myArray = new TElem[this->capacity]; //aloca memorie pentru un array de obiecte de forma TElem

}

Map::~Map() {
	//TODO - Implementation1
    delete[] this->myArray; //macht den Speicher von myarray frei,Q(1)
}

TValue Map::add(TKey c, TValue v) {             //O(n)-allgemeine Cpmplexitat
    //TODO - Implementation1

    for (int i=0;i<this->length;i++) {
        if (this->myArray[i].first == c) {                  //daca gaseste cheia c , retine valoarea v
            TValue old_value = this->myArray[i].second;     //Q(1)-daca cheia e pe prima pozitie  -best case
            this->myArray[i].second = v;                    //Q(n)-daca cheia e pe ultima pozitie  -worst case
            return old_value;                               //Q(n)-daca cheia e pe pozitia din mijloc  -average case
        }
    }                                                      //Q(1)-amortisiert
     if (this->length==this->capacity){
         resize_up();}


     this->myArray[this->length]=TElem (c,v);
     this->length++;
     return NULL_TVALUE;
    }

TValue Map::search(TKey c) const{                    //Q(n)-daca cheia e pe pozitia din mijloc  -average case
	//TODO - Implementation1                         //Q(n)-daca cheia e pe ultima pozitie  -worst case
    for (int i=0;i<this->length;i++){               //Q(1)-daca cheia e pe prima pozitie  -best case
        if(this->myArray[i].first==c)              //parcurge vectorul si daca gaseste cheia c returneaza valoarea ei
            return this->myArray[i].second;
    }                                              //O(n)-allgemeine Komplexitat
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//TODO - Implementation

    if (this->length==this->capacity/4) {
        resize_down();                              //
    }

    int i;
    int found=0;
    TValue myvalue;
    for (i=0;i<this->length;i++) {
        if (this->myArray[i].first == c) {
            myvalue=this->myArray[i].second;                  //sterge cheia c si returneaza valoarea cheii respective
            found=1;
            for(int j=i+1;j<=this->length-1;j++)             //Q(n)  -si daca il gaseste tot pe prima pozitie -best case
                this->myArray[j-1]=this->myArray[j];         //Q(n) -daca cheia e pe ultima pozitie  -worst case
            this->length--;                                  //Q(n)-daca cheia e pe pozitia din mijloc  -average case

            break;
        }                                                  //O(n)-allgemeine Komplexitat
    }                                                      //Q(1)-amortisiert


    if(found==1)
        return myvalue;


	return NULL_TVALUE;
}


int Map::size() const {
	//TODO - Implementation1
    return this->length;      // lungimea lui Map
}                              //Q(1) -complexitate

bool Map::isEmpty() const{
	//TODO - Implementation1
    if(this->length==0)    //daca lungimea este 0 => Map este empty
        return true;       //Q(1)-complexitate
	return false;
}

void Map::resize_up() {
    this->capacity = this->capacity*2;                      //capacitatea devine dubla
    TElem *newArray ;                                        //facem un nou pointer
    newArray= new TElem[this->capacity];                     //alocam memorie
    for (int i=0;i<this->length;i++)
        newArray[i]=this->myArray[i];                              //copiem toate elementele din vector in noual array


    delete[]  this->myArray;                                     // stergem   Q(n)
    this->myArray=newArray;                                      //copiem pointerul nou in cel vechi
}

void Map::resize_down() {
    this->capacity= this->capacity/2;                    //micsoram capacitatea
    TElem *newArray ;
    newArray= new TElem[this->capacity];                //alocam memorie
    for (int i=0;i<this->length;i++) {
        newArray[i] = this->myArray[i];                           //copiem toate elementele din vector in noual array
    }
    delete[]  this->myArray;                               //dealocam memorie    Q(n)
    this->myArray=newArray;                                //copiem pointerul nou in cel vechi

}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}

MapIterator Map ::iterator1(int n) const {
    return MapIterator(*this);
}



#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {

    this->r = r;
    this->head = -1;
    this->capacity = 10;
    elems = new std::pair<TElem, int>[this->capacity];
    next = new int[this->capacity];
    for( int i = 0; i < capacity; i++){            //Q(n)-complexitate
        next[i] = i + 1;
    }
    next[capacity - 1] = -1;
    firstEmpty = 0;
}

void SortedBag::add(TComp e) {

    if(firstEmpty == -1){
        resizeUp();
    }

    int current = head;
    int prev = -1;
                                                             //BC Q(1) ,AC Q(n) ,WC(n)
    while(current != -1 && r(elems[current].first, e)){
        prev = current;
        current = next[current];
    }
    if(current == head){                       //trebuie adaugat pe prima pozitie
        int newPos = firstEmpty;
        firstEmpty = next[firstEmpty];
        next[newPos] = head;
        head = newPos;
        elems[newPos]={e,1};
    }
    else if(elems[prev].first==e) {         //daca elemntul exista deja vom creste doar frecventa
        elems[prev].second++;
    }
    else {
        int newPos = firstEmpty;
        firstEmpty = next[firstEmpty];
        next[newPos] = next[prev];         //adaugam pe o pozitie oarecare
        next[prev] = newPos;
        elems[newPos]={e,1};
    }
}


bool SortedBag::remove(TComp e) {
    int current = head;
    int prev = -1;
    while(current != -1 && elems[current].first != e){      //BC Q(1) ,AC Q(n) ,WC(n)
        prev = current;
        current = next[current];
    }
    if(current != -1){
        if(current == head && elems[current].second == 1){   //verificam daca este pe pozitia de head
            head = next[current];
            next[current] = firstEmpty;
            firstEmpty = current;
        }
        else if(elems[current].second == 1){    //nu este head
            next[prev] = next[current];
            next[current] = firstEmpty;
            firstEmpty = current;
        }
        else{
            elems[current].second --;
        }
        return true;
    }
	else{
        return false;
    }
}


bool SortedBag::search(TComp elem) const {
    int current = head;                                        //Q(1)-BC se gaseste pe prima pozitie
    while(current != -1 && elems[current].first != elem &&r(elems[current].first,elem)){      //Q(n)-AC se gaseste pe pozitia din mijloc
        current = next[current];                               //Q(n)-WC se gaseste pe ultima pozitie sau nu se gaseste
    }                                                          //O(n)-allgemeine Komplexitat
    if(elems[current].first == elem && current!=-1){
        return true;
    }
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {

    int current = head;
    while(elems[current].first != elem && current!=-1){    //Q(1)-BC se afla pe prima pozitie
        current = next[current];                           //Q(n)-AC se afla pe o pozitie din mijloc
    }                                                      //Q(n)-WC nu il gaseste sau ultima pozitie
    if(current==-1)                                        //O(n) -allgemeine Komplexitat
        return 0;
	return elems[current].second;
}



int SortedBag::size() const {
    int size = 0;
    int current = head;
    while(current != -1){
        size = size + elems[current].second;        //Q(n)-Komplexitat
        current = next[current];
    }
	return size;
}


bool SortedBag::isEmpty() const {

    if(head == -1){
        return true;             //Q(1)-Komplexitat
    }
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    delete[] next;
    delete[] elems;            //Q(n) Komplexitat
}                             //dealocam

void SortedBag::resizeUp() {
    int ogCap = this->capacity;
    this->capacity = ogCap * 2;
    std::pair<TElem,int> *newElems = new std::pair<TElem ,int>[capacity];
    int *newNext = new int[capacity];
    for (int i = 0; i < ogCap; i++) {
        newElems[i] = elems[i];
        newNext[i] = next[i];                                  //Q(n)-complexitate
    }
    delete[] elems;
    delete[] next;
    elems = newElems;
    next = newNext;
    for( int i = ogCap; i < capacity; i++){
        next[i] = i + 1;
    }
    next[capacity - 1] = -1;
    firstEmpty = ogCap;

}
//intersechitia a 2 containere

SortedBag SortedBag::intersection(SortedBag other) const{
    SortedBag result(this->r);   //rezultatul celor 2
    int current=this->head;


    while(this->next[current]!=-1) {
        TComp elem=this->elems[current].first;
        int current1 = other.head;
        while(current1 != -1 && other.elems[current1].first != elem && other.r(other.elems[current1].first,elem)){
            current1 = other.next[current1];
        }
        if(other.elems[current1].first == elem && current1!=-1){
            if(result.firstEmpty == -1){
                result.resizeUp();
            }

            int current_result = result.head;
            int prev = -1;

            while(current_result != -1 && result.r(result.elems[current_result].first, elem)){
                prev = current_result;
                current_result = result.next[current_result];
            }
            if(current_result == result.head){                       //trebuie adaugat pe prima pozitie
                int newPos = result.firstEmpty;
                result.firstEmpty = result.next[result.firstEmpty];
                result.next[newPos] = result.head;
                result.head = newPos;
                result.elems[newPos]={elem,1};
            }

            else {
                int newPos = result.firstEmpty;
                result.firstEmpty = result.next[result.firstEmpty];
                result.next[newPos] = result.next[prev];         //adaugam pe o pozitie oarecare
                result.next[prev] = newPos;
                result.elems[newPos]={elem,1};
            }
        }
       current=this->next[current];
    }
    return result;


}
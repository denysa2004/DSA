#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    this->head= nullptr;
    this->tail= nullptr;            //relatia cu r
    relation=r;                     //initializam head si tail cu nulllptr
}                                   //complexitate Q(1)

int SortedIteratedList::size() const {
    int number=0;                          //numarul tuturor elementelor
    Node *currentnode=this->head;          //initializam nodul curent cu head
    while(currentnode!= nullptr){          //iteram prin noduri pana ajungem la tail ,crestem contorul si trecem la urmatorul nod
        number++;                          //Q(n)-complexitate
        currentnode=currentnode->next;
    }
    return number;

}

bool SortedIteratedList::isEmpty() const {
    if(this->head == nullptr) {
                                         //daca primul nod este pointerul null atunci lista e goala
        return true;
    }                                   //complexitate Q(1)
	return false;
}

ListIterator SortedIteratedList::first() const {
	 return ListIterator(*this);            //Q(1)-Komplexitat
                                            //un obiect ListIterator care indica catre primul element

}

TComp SortedIteratedList::getElement(ListIterator poz) const {

    if(!poz.valid())
        throw exception();            //Q(1)-complexitate
    return poz.getCurrent();          //daca pozitia este valida returnam elementul altfel exceptie

	return NULL_TCOMP;
}

TComp SortedIteratedList::remove(ListIterator& poz) {

    if(!poz.valid())
        throw exception();           //daca pozitia nu este valida ,avem exceptie
    Node *removedNode=poz.it;        //un pointer spre pozitia nodului care trebuie sters
    TComp  removedData=removedNode->data; //vom retine datele nodului care trebuie sters

                                                               //Q(1)-beste case,daca pozitia e pe primul nod
    //daca nodul nu este head                                  //Q(n)-average case ,pe pozitia din mijloc
    if(removedNode->previous!= nullptr)                        //Q(n)-best case ,pe ultima pozitie sau nu se gaseste
        removedNode->previous->next=removedNode->next;
    else  //daca nodul este head
        head=removedNode->next;
    //daca nodul nu este tail
    if(removedNode->next!= nullptr)
        removedNode->next->previous=removedNode->previous;
    else //daca nodul este tail
        tail=removedNode->previous;
    //dupa ce stergem nodul pozitia trece la urmatorul nod care nu a fost sters
   poz.next();
   delete removedNode; //dealocam removedNode
   return removedData;//afisam elementul sters
   return NULL_TCOMP;
}


ListIterator SortedIteratedList::search(TComp e) const {

    ListIterator iterator=first();              //un iterator catre primul element
    while(iterator.valid()) {
        if(iterator.getCurrent()==e)            //best case Q(1)-il gasim ca fiind primul nod
            return iterator;                    //average case Q(n)-se gaseste pe pozitia din mijloc
        iterator.next();                        //worst case Q(n)-pe ultima pozitie sau nu este deloc
    }                                           //O(n)-allgemeine Komplexitat
    return iterator;                           //nu a fost gasit elementul

}


void SortedIteratedList::add(TComp e) {
    Node *newNode = new Node;          //se creeaza un nou nod
    newNode->data = e;                 //datele noului nod
    newNode->next = nullptr;           //un pointer catre nextul nodului
    newNode->previous = nullptr;       //un pointer catre previous

    if (isEmpty()) {
        head = newNode;            //verificam daca lista este goala si initializam atat head cat si tail cu newnode
        tail = newNode;
    } else {
        Node *current = head;      //un pointer catre inceputul cozii
        Node *prev = nullptr;

        while (current != nullptr && relation(current->data, e)) {      //iteram lista si gasim pozitia unde trebuie adaugat
            prev = current;
            current = current->next;                       //Best Case Q(1) -gasim pe prima pozitie
        }                                                  //Average Case Q(n) - il gasim pe pozitia din mijloc
                                                           //Worst Case Q(n)   -il gasim pe ultima pozitie sau nu il gasim
        if (prev == nullptr) {
            newNode->next = head;             //adaugam la inceputul listei
            head->previous = newNode;
            head = newNode;
        } else if (current == nullptr) {
            prev->next = newNode;
            newNode->previous = prev;        //adaugam la sfarsitul listei
            tail = newNode;
        } else {
            prev->next = newNode;
            newNode->previous = prev;
            newNode->next = current;         //adugam la mijlocul listei
            current->previous = newNode;
        }
    }
}



SortedIteratedList::~SortedIteratedList() {

    Node *currenNode=head;                //initializam un pointer la primul nod
    while(currenNode!= nullptr)
    {                                      //complexitate  Q(n)
        Node *nextNode;                    //pointer catre urmatorul nod
        nextNode=currenNode->next;         //parcurgem toate nodurile si le dealocam
        delete currenNode;                 //stergem nodul curent
        currenNode=nextNode;
    }
}

/*void addAll(const SortedIteratedList<TComp>& otherList) {
    if (otherList.isEmpty()) {
        return;                   //lista e goala nu facem nimic
    }

    Node* currentOther = otherList.head;   //declaram un pointer catre prima lista

    while (currentOther != nullptr) {      //parcurgem lista si le adaugam
        add(currentOther->data);
        currentOther = currentOther->next;
    }
}*/
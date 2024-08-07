#include "SortedSetIterator.h"
#include <exception>

using namespace std;


SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    first();                 //complexitate Q(n)
}

void SortedSetIterator::first() { //complexitate Q(n)
    array.capacity = multime.size();
    array.top = -1;
    array.stack = new BTSNode[array.capacity];
    inorder(multime.head);


    if (multime.head == nullptr)
        iterator = nullptr;
    else
        iterator = &array.stack[0];
}

void SortedSetIterator::inorder(struct BTSNode *currentNode) { //complexitate Q(n)
    if (currentNode == nullptr)
        return;

    inorder(currentNode->left);

    array.top++;
    array.stack[array.top] = *currentNode;

    inorder(currentNode->right);
}

void SortedSetIterator::next() { //Q(1)-complexitate
    if (!valid())
        throw exception();
    else
    {
        iterator++;
        if (!valid())
            iterator = nullptr;
    }
}

TElem SortedSetIterator::getCurrent()
{
    if (valid()) {                    //Q(1)-complexitate
        return iterator->data;
    }
    else
        throw exception();
}

bool SortedSetIterator::valid() const {
    if (iterator >= &array.stack[0] && iterator < &array.stack[array.capacity])   //Q(1)-complexitate
        return true;
    return false;
}

SortedSetIterator::~SortedSetIterator() { //complexitate Q(n)
    delete[] array.stack;
}





#include "SortedSet.h"

#include <iostream>
#include <vector>

#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	head=nullptr;
	relation=r;                                //complexitate Q(1)
}



bool SortedSet::add(TComp elem) {                                //Q(n),Q(logn),Q(1) -complexitate
	BTSNode* newN = new BTSNode{elem, nullptr, nullptr };
	bool operation;

	if (head == nullptr) {
		head = newN;       // daca nu avem nod in arbore
        operation=true;
		return operation;
	}

	BTSNode* currentNode = head;

	while (currentNode != nullptr) {
		if (elem == currentNode->data) {
			delete newN;                      //elementul exista deja in arbore
			operation=false;
			return operation;

		}

		else if (!relation(elem, currentNode->data)) {
			if (currentNode->right == nullptr) {       //cautam in subarborele drept
				currentNode->right = newN;
				operation=true;
				return operation;
			}
			currentNode = currentNode->right;
		}
		else {
			if (currentNode->left == nullptr) {
				currentNode->left = newN;         //cautam in subarborele stang
				operation=true;
				return operation;
			}

			currentNode = currentNode->left;
		}
	}
	operation=false;
	return operation;
}

bool SortedSet::remove(TComp elem) {      //Q(n),Q(logn),Q(1) -complexitate
	BTSNode* currentNode = head;
	BTSNode* parentNode = nullptr;

	while (currentNode != nullptr && currentNode->data != elem) {
		parentNode = currentNode;
		if (relation(elem, currentNode->data)) {
			currentNode = currentNode->left;         //gasim nodul care trebuie eliminat
		} else {
			currentNode = currentNode->right;
		}
	}
	//nodul nu a fost gasit
	if (currentNode == nullptr) return false;

	// Nodul are doi copii
	if (currentNode->left != nullptr && currentNode->right != nullptr) {
		BTSNode* successorParent = currentNode;
		BTSNode* successor = currentNode->right;
		while (successor->left != nullptr) {
			successorParent = successor;      //gasesc cel mai mic nod
			successor = successor->left;
		}

		currentNode->data = successor->data;
		currentNode = successor;   //elementul care trebuie sters
		parentNode = successorParent;
	}

	// Nodul are cel mult un copil
	BTSNode* childNode;
	if (currentNode->left != nullptr) {//daca are copil stanga
		childNode = currentNode->left;
	} else {
		childNode = currentNode->right;//daca are copil dreapta sau nu are copil
	}

	if (parentNode == nullptr) {    //currentNode este radacina arborelui
		head = childNode;
	} else {
		if (relation(currentNode->data, parentNode->data)) { //verificam daca currentNode este copilul stang sau drept
			parentNode->left = childNode;
		} else {
			parentNode->right = childNode;
		}
	}

	delete currentNode;
	return true;
}


bool SortedSet::search(TComp elem) const {
	BTSNode *currentNode= head;
    bool found = false;
	while (currentNode != nullptr && found==false) {
		if (currentNode->data == elem)                  // worst = θ(n)
			found=true;                                 // average = θ(log n)
		if (!relation(elem, currentNode->data)) {      // best = θ(1)
			currentNode = currentNode->right;
		}
		else {
			currentNode = currentNode->left;
		}
	}
	return found;
}



int SortedSet::size() const {
	return sizeR(head);

}
int SortedSet::sizeR(BTSNode* node) const {
	if (node == nullptr) {
		return 0;                                    //Q(n)-complexitate
	}
	int leftCount = sizeR(node->left);
	int rightCount = sizeR(node->right);

	return leftCount + rightCount + 1;
}


bool SortedSet::isEmpty() const {
	if (head==nullptr)
		return true;                             //Q(1)-complexitate
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	deleteRec(head);                 //Q(1)-delete recursiv
}


void SortedSet::deleteRec(BTSNode* current) {
	if (current == nullptr)    //daca nodul este null ,nu avem ce dealoca
		return;

	deleteRec(current->right);          //Q(n)-complexitate
	deleteRec(current->left);
	delete current;

}


int SortedSet::inorderDifference(SortedSet s, SortedSet other) {
	BTSNode *currentNode= head;
	BTSNode *currentNode1=other.head;

	int count=0;
	while(count<s.size()){
		bool found=false;
		while (currentNode != nullptr && found == false) {
			if (currentNode->data == currentNode1->data)
				found=true;
			if (!relation(currentNode1->data, currentNode->data))
			{
				currentNode1 = currentNode1->right;
			}
			else {
				currentNode1 = currentNode1->left;
			}
		}
		if(found==false)
			std::cout<<currentNode->data;

		count++;
		if(currentNode->right!=nullptr)
			currentNode->right;
		else{
			currentNode->left;
		}

	}
}




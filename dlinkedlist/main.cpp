#include <iostream>

using namespace std;

struct element {
	int value;
	element* previous = nullptr;
	element* next = nullptr;
};

void addLast(element** lista, int newValue) {
	element* nowy = new element;

	nowy->value = newValue;
	nowy->next = nullptr;

	if (*lista == nullptr) {
		nowy->previous = nullptr;
		*lista = nowy;
		return;
	}

	element* ostatni = new element;
	ostatni = *lista;
	while (ostatni->next != nullptr) {
		ostatni = ostatni->next;
	}
	ostatni->next = nowy;
	nowy->previous = ostatni;
}

void addFirst(element** lista, int newValue) {
	element* nowy = new element;

	nowy->value = newValue;
	nowy->previous = nullptr;
	nowy->next = *lista;

	if (*lista != nullptr) {
		(*lista)->previous = nowy;
	}

	*lista = nowy;
}

void addAfter(element* previousElement, int newValue) {
	element* nowy = new element;
	nowy->value = newValue;

	nowy->previous = previousElement;
	nowy->next = previousElement->next;

	previousElement->next = nowy;

	if (nowy->next != nullptr) {
		nowy->next->previous = nowy;
	}
}

void print(element** lista) {
	element* i = *lista;
	while (i != nullptr) {
		cout << i->value << "\t";
		i = i->next;
	}
	cout << endl;
}

element* findValue(element** lista, int searchValue) {
	if (*lista == nullptr) return nullptr;
	element* i = new element;
	i = *lista;
	while (i->value != searchValue) {
		if (i->next == nullptr) {
			return nullptr;
		}
		i = i->next;
	}

	return i;
}

void deleteElement(element** lista, element* toDelete) {
	if (*lista == toDelete) {
		*lista = (*lista)->next;
	}

	if (toDelete->next != nullptr) {
		toDelete->next->previous = toDelete->previous;
	}

	if (toDelete->previous != nullptr) {
		toDelete->previous->next = toDelete->next;
	}
	delete toDelete;
}

void deleteList(element** lista) {
	element* i = (*lista)->next;
	while (i != nullptr) {
		delete i->previous;
		i = i->next;
	}
}

void bubbleSort(element** lista, bool reverse = false) {
	element* i = *lista;
	bool notSorted = true;
	int tempVal;
	if (!reverse) {
		while (notSorted) {
			i = *lista;
			notSorted = false;
			while (i->next != nullptr) {
				if (i->value > i->next->value) {
					notSorted = true;
					tempVal = i->value;
					i->value = i->next->value;
					i->next->value = tempVal;
				}
				i = i->next;
			}
		}
	}
	else {
		while (notSorted) {
			i = *lista;
			notSorted = false;
			while (i->next != nullptr) {
				i = i->next;
			}
			while (i->previous != nullptr) {
				if (i->value < i->previous->value) {
					notSorted = true;
					tempVal = i->value;
					i->value = i->previous->value;
					i->previous->value = tempVal;
				}
				i = i->previous;
			}
		}
	}
	
}

void deleteLast(element** lista)
{
	if (*lista == nullptr) return;

	element* ostatni = *lista;
	while (ostatni->next != nullptr) {
		ostatni = ostatni->next;
	}

	if (ostatni->previous != nullptr) {
		ostatni->previous->next = nullptr;
	}
	else {
		*lista = nullptr;
	}

	delete ostatni;
}

void deleteFirst(element** lista)
{
	if (*lista == nullptr) return;
	element* pierwszy = *lista;

	*lista = (*lista)->next;
	(*lista)->previous = nullptr;

	delete pierwszy;
}

int main() {
	element* lista = nullptr;
	addLast(&lista, 3);
	addLast(&lista, 7);
	addLast(&lista, 8);
	addAfter(findValue(&lista, 8), 5);
	addLast(&lista, 4);
	addFirst(&lista, 2);
	print(&lista);
	deleteElement(&lista, findValue(&lista, 8));
	addAfter(findValue(&lista, 7), 44);
	cout << "\n\n";
	bubbleSort(&lista, true);
	print(&lista);
	
	deleteLast(&lista);
	print(&lista);
	deleteFirst(&lista);
	print(&lista);
	deleteList(&lista);
	return 0;
}
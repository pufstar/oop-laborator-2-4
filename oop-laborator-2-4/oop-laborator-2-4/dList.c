#include <stdlib.h>
#include <assert.h>
#include "dList.h"
#include "offer.h"
#include "service.h"

/*
* Creates a new dynamic list
* Input:
*	capacity - the initial # of elements of the list
* Output:
*	list - the empty list that has been created
*/
dynamicList create_list(int capacity) {
	dynamicList list;

	list.capacity = capacity;
	list.currentSize = 0;
	list.elems = malloc(capacity * sizeof(Offer));

	return list;
}

/*
* Doubles the size of a given dynamically allocated list
* by creating a new one and copying the old one
* Input:
*	list - the old list
* Output:
*	newList - the new list, with double the size of the old one
*/
dynamicList resize_list(dynamicList *list) {

	Offer *newList = malloc(sizeof(Offer) * list->capacity * 2);

	for (int i = 0; i < list->currentSize; ++i) {
		newList[i] = list->elems[i];
	}

	free(list->elems);

	list->elems = newList;
	list->capacity *= 2;
}

/*
* Destroys the list by deallocating its components
* Input:
*	list - the list to be destroyed
*/
void destroy_list(dynamicList* list) {
	for (int i = 0; i < list->currentSize; ++i) {
		destroy_offer(&list->elems[i]);
	}
	free(list->elems);
}

/*
* Appends a new offer to a dynamically allocated list
* Input:
*	list - the list where the new item will be appended
*	offer - the item to be appended
*/
void add_offer(dynamicList *list, Offer offer) {
	if (list->capacity == list->currentSize) {
		resize_list(list);
	}

	list->elems[list->currentSize++] = offer;
}

/*
* Removes an offer from a list
* Input:
*	list - the list where the offer will be removed from
*	pos - the position of the element
*/
void remove_offer(dynamicList *list, int pos) {
	destroy_offer(&list->elems[pos - 1]);
	for (int i = pos - 1; i < list->currentSize - 1; ++i) {
		list->elems[i] = get_offer(list, i + 2);
	}
	list->currentSize--;
}

/*
* Changes an offer by replacing it with a new one
* Input:
*	list - he list of offers
*	pos - the position of the offer to be replaced
*	newOffer - the offer to replace the old one
*/
Offer replace_offer(dynamicList* list, int pos, Offer newOffer) {
	Offer oldOffer = list->elems[pos - 1];
	list->elems[pos - 1] = newOffer;
	return oldOffer;
}

/*
* Returns the element from the given position in the list
*/
Offer get_offer(dynamicList *list, int pos) {
	return list->elems[pos - 1];
}

/*
* Returns a deep-copy of the list given by parameter
* Input:
*	list - the list to be copied
* Output:
*	newList - the copied list
*/
dynamicList copy_list(dynamicList* list) {
	dynamicList newList = create_list(2);

	for (int i = 0; i < list->currentSize; ++i) {
		Offer off = get_offer(list, i + 1);
		add_offer(&newList, copy_offer(&off));
	}

	return newList;
}

void test_create_list() {
	dynamicList list;
	list = create_list(5);

	assert(list.currentSize == 0);
	assert(list.capacity == 5);

	destroy_list(&list);
}

void test_resize_list() {
	dynamicList list;
	list = create_list(5);

	resize_list(&list);

	assert(list.currentSize == 0);
	assert(list.capacity == 10);

	destroy_list(&list);
}

void test_add_offer() {
	dynamicList list;
	list = create_list(2);
	
	Offer of1 = create_offer("mare", "Hawaii", "11/07/2019", "3400");
	Offer of2 = create_offer("munte", "Alaska", "11/11/2019", "4400");
	Offer of3 = create_offer("munte", "Everest", "17/12/2019", "3200");

	add_offer(&list, of1);
	add_offer(&list, of2);
	add_offer(&list, of3);


	assert(list.capacity == 4);
	assert(list.currentSize == 3);

	destroy_list(&list);
}

void test_remove_offer() {
	dynamicList list;
	list = create_list(2);

	Offer of1 = create_offer("mare", "Hawaii", "11/07/2019", "3400");
	Offer of2 = create_offer("munte", "Alaska", "11/11/2019", "4400");
	Offer of3 = create_offer("munte", "Everest", "17/12/2019", "3200");

	add_offer(&list, of1);
	add_offer(&list, of2);
	add_offer(&list, of3);

	remove_offer(&list, 2);

	assert(list.capacity == 4);
	assert(list.currentSize == 2);

	Offer goff = get_offer(&list, 2);
	assert(strcmp(goff.type, "munte") == 0);
	assert(strcmp(goff.destination, "Everest") == 0);
	assert(strcmp(goff.departDate, "17/12/2019") == 0);
	assert(goff.price == 3200);

	destroy_list(&list);
}

void test_get_offer() {
	dynamicList list;
	list = create_list(2);

	Offer of1 = create_offer("mare", "Hawaii", "11/07/2019", "3400");
	Offer of2 = create_offer("munte", "Alaska", "11/11/2019", "4400");
	Offer of3 = create_offer("munte", "Everest", "17/12/2019", "3200");

	add_offer(&list, of1);
	add_offer(&list, of2);
	add_offer(&list, of3);

	Offer goff = get_offer(&list, 2);

	assert(strcmp(goff.type, "munte") == 0);
	assert(strcmp(goff.destination, "Alaska") == 0);
	assert(strcmp(goff.departDate, "11/11/2019") == 0);
	assert(goff.price == 4400);

	destroy_list(&list);
}

void test_copy_list() {
	dynamicList list;
	list = create_list(2);

	Offer of1 = create_offer("mare", "Hawaii", "11/07/2019", "3400");
	Offer of2 = create_offer("munte", "Alaska", "11/11/2019", "4400");
	Offer of3 = create_offer("munte", "Everest", "17/12/2019", "3200");

	add_offer(&list, of1);
	add_offer(&list, of2);
	add_offer(&list, of3);

	dynamicList newList = copy_list(&list);

	Offer goff = get_offer(&newList, 2);
	assert(strcmp(goff.type, "munte") == 0);
	assert(strcmp(goff.destination, "Alaska") == 0);
	assert(strcmp(goff.departDate, "11/11/2019") == 0);
	assert(goff.price == 4400);

	destroy_list(&newList);
	destroy_list(&list);
}
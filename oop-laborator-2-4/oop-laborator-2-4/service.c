#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "offer.h"
#include "dList.h"
#include "sort.h"

/*
* Validates the parameters for a new offer
* Input:
*	type, destination, depart date, price
* Output:
*	0 if the data is not ok
*	1 if the data is ok
*/
int validate(char type[20], char destination[20], char departDate[20], char price[20]) {
	if (strcmp(type, "") == 0 || strcmp(destination, "") == 0 || strcmp(departDate, "") == 0 || strcmp(price, "") == 0) {
		return 0;
	}
	if (strcmp(type, "munte") != 0 && strcmp(type, "mare") != 0 && strcmp(type, "city_break") != 0) {
		return 0;
	}
	for (int i = 0; i < strlen(destination); ++i) {
		if (!((destination[i] >= 'a' && destination[i] <= 'z') || (destination[i] >= 'A' && destination[i] <= 'Z'))) {
			return 0;
		}
	}
	if (strlen(departDate) != 10) {
		return 0;
	}
	if (!(departDate[0] >= '0' && departDate[0] <= '9' && departDate[1] >= '0' && departDate[1] <= '9'
		&& departDate[2] == '/' && departDate[3] >= '0' && departDate[3] <= '9' && departDate[4] >= '0' && departDate[4] <= '9'
		&& departDate[5] == '/' && departDate[6] >= '0' && departDate[6] <= '9' && departDate[7] >= '0' && departDate[7] <= '9'
		&& departDate[8] >= '0' && departDate[8] <= '9' && departDate[9] >= '0' && departDate[9] <= '9')) {
		return 0;
	}
	for (int i = 0; i < strlen(price); ++i) {
		if (!(price[i] >= '0' && price[i] <= '9')) {
			return 0;
		}
	}

	return 1;
}

/*
* Compares the price of two offers
* Output:
*	-1 if off1 < off2
*	 0 if off1 = off2
*	 1 if off1 > off2
*/
int cmp_price(Offer* off1, Offer* off2) {
	if (off1->price == off2->price)
		return 0;
	else if (off1->price < off2->price)
		return -1;
	else {
		return 1;
	}
}

/*
* Compares the destinations of two offers
* Output:
*	-1 if off1 < off2
*	 0 if off1 = off2
*	 1 if off1 > off2
*/
int cmp_destination(Offer* off1, Offer* off2) {
	return strcmp(off1->destination, off2->destination);
}

/*
* Sorts the list by the price of the offers
* Input:
*	list - the list to be sorted
* Output:
*	newList - the sorted list
*/
dynamicList sort_by_price(dynamicList* list) {
	dynamicList newList = copy_list(list);
	sort_list(&newList, cmp_price);
	return newList;
}

/*
* Sorts the list by the destination of the offers
* Input:
*	list - the list to be sorted
* Output:
*	newList - the sorted list
*/
dynamicList sort_by_destination(dynamicList* list) {
	dynamicList newList = copy_list(list);
	sort_list(&newList, cmp_destination);
	return newList;
}

/*
* Filters the list using a given criteria and a key
* Input:
*	list - the list to be filtered
*	criteria - the criteria by which the list is filtered
*	key - the key for the filtre
* Output:
*	filteredList - the filtered list
*/
dynamicList filter_list(dynamicList* list, char criteria[20], char key[20]) {
	dynamicList filteredList = create_list(2);
	if (strcmp(criteria, "type") == 0) {
		for (int i = 1; i <= list->currentSize; ++i) {
			Offer off = get_offer(list, i);
			if (strcmp(off.type, key) == 0) {
				add_offer(&filteredList, off);
			}
		}
	}
	else if (strcmp(criteria, "destination") == 0) {
		for (int i = 1; i <= list->currentSize; ++i) {
			Offer off = get_offer(list, i);
			if (strcmp(off.destination, key) == 0) {
				add_offer(&filteredList, off);
			}
		}
	}
	else if(strcmp(criteria, "price") == 0) {
		for (int i = 1; i <= list->currentSize; ++i) {
			Offer off = get_offer(list, i);
			char price[20];
			sprintf(price, "%d", off.price);
			if (strcmp(price, key) == 0) {
				add_offer(&filteredList, off);
			}
		}
	}
	return filteredList;
}

void test_validate() {
	assert(validate("", "", "", "") == 0);
	assert(validate("sadfasdf", "hiji", "11/11/2017", "190") == 0);
	assert(validate("munte", "", "11/11/2017", "1111") == 0);
	assert(validate("munte", "hiji1", "11/11/2017", "312312") == 0);
	assert(validate("munte", "alaska", "11.11.2017", "12312") == 0);
	assert(validate("munte", "alaska", "11.11.20178", "12312") == 0);
	assert(validate("munte", "alaska", "34/15/2999", "12312") == 1);
	assert(validate("munte", "alaska", "11/11/2017", "abc") == 0);
	assert(validate("munte", "alaska", "11/11/2017", "1234") == 1);

}

void test_cmp_price() {
	Offer off1 = create_offer("munte", "bucegi", "11/11/1111", "5000");
	Offer off2 = create_offer("munte", "bucega", "11/11/1111", "3000");
	Offer off3 = create_offer("munte", "bucege", "11/11/1111", "4000");
	Offer off4 = create_offer("city_break", "bucege", "11/11/1111", "4000");

	assert(cmp_price(&off1, &off2) == 1);
	assert(cmp_price(&off2, &off3) == -1);
	assert(cmp_price(&off3, &off4) == 0);

	destroy_offer(&off1);
	destroy_offer(&off2);
	destroy_offer(&off3);
	destroy_offer(&off4);
}

void test_cmp_destination() {
	Offer off1 = create_offer("munte", "bucegi", "11/11/1111", "5000");
	Offer off2 = create_offer("munte", "bucega", "11/11/1111", "3000");
	Offer off3 = create_offer("munte", "bucege", "11/11/1111", "4000");
	Offer off4 = create_offer("city_break", "bucege", "11/11/1111", "4000");

	assert(cmp_destination(&off1, &off2) == 1);
	assert(cmp_destination(&off2, &off3) == -1);
	assert(cmp_destination(&off3, &off4) == 0);

	destroy_offer(&off1);
	destroy_offer(&off2);
	destroy_offer(&off3);
	destroy_offer(&off4);
}

void test_sort_by_price() {
	dynamicList list;
	list = create_list(2);

	Offer off1 = create_offer("munte", "bucegi", "11/11/1111", "5000");
	Offer off2 = create_offer("munte", "bucega", "11/11/1111", "3000");
	Offer off3 = create_offer("munte", "bucege", "11/11/1111", "4000");

	add_offer(&list, off1);
	add_offer(&list, off2);
	add_offer(&list, off3);

	dynamicList sortedList = sort_by_price(&list);

	assert(sortedList.elems[0].price == 3000);

	destroy_list(&list);
	destroy_list(&sortedList);
}

void test_sort_by_destination() {
	dynamicList list;
	list = create_list(2);

	Offer off1 = create_offer("munte", "bucegi", "11/11/1111", "5000");
	Offer off2 = create_offer("munte", "bucega", "11/11/1111", "3000");
	Offer off3 = create_offer("munte", "bucege", "11/11/1111", "4000");

	add_offer(&list, off1);
	add_offer(&list, off2);
	add_offer(&list, off3);

	dynamicList sortedList = sort_by_destination(&list);

	assert(strcmp(sortedList.elems[0].destination, "bucega") == 0);

	destroy_list(&list);
	destroy_list(&sortedList);
}

void test_filter_list() {
	dynamicList list;
	dynamicList filteredList;
	list = create_list(2);

	Offer off1 = create_offer("munte", "bucegi", "11/11/1111", "3535");
	Offer off2 = create_offer("mare", "bucega", "11/11/1111", "3000");
	Offer off3 = create_offer("city_break", "bucege", "11/11/1111", "3535");
	Offer off4 = create_offer("munte", "bucegi", "11/11/1111", "3535");
	Offer off5 = create_offer("mare", "bucega", "11/11/1111", "3535");
	Offer off6 = create_offer("city_break", "bucege", "11/11/1111", "3535");
	Offer off7 = create_offer("munte", "bucegi", "11/11/1111", "3535");
	Offer off8 = create_offer("munte", "bucegi", "11/11/1111", "3535");
	Offer off9 = create_offer("mare", "bucegi", "11/11/1111", "4000");

	add_offer(&list, off1);
	add_offer(&list, off2);
	add_offer(&list, off3);
	add_offer(&list, off4);
	add_offer(&list, off5);
	add_offer(&list, off6);
	add_offer(&list, off7);
	add_offer(&list, off8);
	add_offer(&list, off9);

	filteredList = filter_list(&list, "type", "munte");
	assert(filteredList.currentSize == 4);
	free(filteredList.elems);

	filteredList = filter_list(&list, "destination", "bucegi");
	assert(filteredList.currentSize == 5);
	free(filteredList.elems);

	filteredList = filter_list(&list, "price", "3535");
	assert(filteredList.currentSize == 7);
	free(filteredList.elems);

	destroy_list(&list);
}
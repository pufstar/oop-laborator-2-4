#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <stdio.h>
#include <string.h>
#include "offer.h"
#include "service.h"
#include "dList.h"
#include "sort.h"
#include "tests.h"

/*
* Prints the command menu
*/
void print_menu() {
	printf("\n1. Add a new offer");
    printf("\n2. Change an offer");
	printf("\n3. Remove an offer");
	printf("\n4. Print sorted offers");
	printf("\n5. Filter offers");
	printf("\nP. Print offers");
	printf("\nx. Exit");
}

/*
* Reads and returns a command given by the user
* Output:
*	cmd - the command
*/
char get_command() {
	char cmd[10];

	printf("\nGive command: ");
	scanf("%s", cmd);

	if (strlen(cmd) > 1)
		return "-1";

	return cmd[0];
}

/*
* Reads, validates and adds a new offer to a given list
* Input:
*	dList - the list where the offer will be 
*/
void add_new_offer(dynamicList* dList) {
	char type[20], destination[20], departDate[20], price[20];

	printf("\nGive offer type (munte, mare, city break): ");
	scanf("%s", type);
	printf("\nGive offer destination: ");
	scanf("%s", destination);
	printf("\nGive offer depart date: ");
	scanf("%s", departDate);
	printf("\nGive offer price: ");
	scanf("%s", price);

	int isValid = validate(type, destination, departDate, price);

	if (isValid == 1) {
		Offer off = create_offer(type, destination, departDate, price);
		add_offer(dList, off);
		printf("\nOffer added succesfully!\n");
	}
	else {
		printf("\nWrong input, please try again.");
	}
}

/*
* Reads and changes the properties of an offer
* Input:
*	dList - the list where the operation will take place
*/
void change_offer(dynamicList* dList) {
	int pos;
	printf("\nGive the index to the offer you wish to change: ");
	scanf("%d", &pos);

	if (pos < 0 || pos > dList->currentSize) {
		printf("\nGiven index is invalid.");
	}
	else {
		char cmd;

		printf("\n1. Change type");
		printf("\n2. Change destination");
		printf("\n3. Change depart date");
		printf("\n4. Change price");
		printf("\nGive command: ");
		scanf("%s", &cmd);

		Offer cOff = get_offer(dList, pos);

		if (cmd == '1') {
			char newType[20];
			printf("\nGive new type: ");
			scanf("%s", newType);

			char price[20];
			sprintf(price, "%d", cOff.price);
			int isValid = validate(newType, cOff.destination, cOff.departDate, price);

			if (isValid == 1) {
				Offer nOffer = create_offer(newType, cOff.destination, cOff.departDate, price);
				replace_offer(dList, pos, nOffer);
			}
			else {
				printf("\nWrong input!");
			}
		}
		else if (cmd == '2') {
			char newDestination[20];
			printf("\nGive new destination: ");
			scanf("%s", newDestination);

			char price[20];
			sprintf(price, "%d", cOff.price);
			int isValid = validate(cOff.type, newDestination, cOff.departDate, price);

			if (isValid == 1) {
				Offer nOffer = create_offer(cOff.type, newDestination, cOff.departDate, price);
				replace_offer(dList, pos, nOffer);
			}
			else {
				printf("\nWrong input!");
			}
		}
		else if (cmd == '3') {
			char newDepartDate[20];
			printf("\nGive new date: ");
			scanf("%s", newDepartDate);

			char price[20];
			sprintf(price, "%d", cOff.price);
			int isValid = validate(cOff.type, cOff.destination, newDepartDate, price);

			if (isValid == 1) {
				Offer nOffer = create_offer(cOff.type, cOff.destination, newDepartDate, price);
				replace_offer(dList, pos, nOffer);
			}
			else {
				printf("\nWrong input!");
			}
		}
		else if (cmd == '4') {
			int newPrice;
			printf("\nGive new price: ");
			scanf("%d", &newPrice);

			int isValid = validate(cOff.type, cOff.destination, cOff.departDate, newPrice);

			if (isValid == 1) {
				Offer nOffer = create_offer(cOff.type, cOff.destination, cOff.departDate, newPrice);
				replace_offer(dList, pos, nOffer);
			}
			else {
				printf("\nWrong input!");
			}
		}
		else {
			printf("\nWrong input!");
		}
	}
}

/*
* Reads the data for the deletion of a given offer from a list
* Input:
*	dList - the list where the offer will be deleted from
*/
void delete_offer(dynamicList* dList) {
	int pos;
	printf("\nGive the index to the offer you wish to remove: ");
	scanf("%d", &pos);

	if (pos < 0 || pos > dList->currentSize) {
		printf("\nGiven index is invalid.");
	}
	else {
		remove_offer(&dList, pos);
	}
}

/*
* Reads the data and prints a sorted list
* Input:
*	dList - the list to be sorted
*/
void print_sorted(dynamicList* dList) {
	char cmd = "";
	printf("\n1. Sort by price");
	printf("\n2. Sort by destination");
	printf("\nGive command:");
	scanf("%s", &cmd);

	if (cmd == '1') {
		dynamicList sortedList = sort_by_price(dList);
		for (int i = 0; i < sortedList.currentSize; ++i) {
			Offer currentOffer = get_offer(&sortedList, i + 1);
			printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
		}
		destroy_list(&sortedList);
	}
	else if (cmd == 2) {
		dynamicList sortedList = sort_by_destination(dList);
		for (int i = 0; i < sortedList.currentSize; ++i) {
			Offer currentOffer = get_offer(&sortedList, i + 1);
			printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
		}
		destroy_list(&sortedList);
	}
	else {
		printf("\nWrong input!");
	}
}

/*
* Reads the data, filters a list and prints the result
* Input:
*	dList - the list to be filtered
*/
void print_filtered(dynamicList* dList) {
	char cmd = "";
	printf("\n1.Filter by type");
	printf("\n2.Filter by destination");
	printf("\n2.Filter by price");
	printf("\nGive command: ");
	scanf("%s", &cmd);

	if (cmd == '1') {
		char key[20];
		printf("\nGive type: ");
		scanf("%s", key);

		dynamicList filteredList = filter_list(dList, "type", key);
		for (int i = 0; i < filteredList.currentSize; ++i) {
			Offer currentOffer = get_offer(&filteredList, i + 1);
			printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
		}
		destroy_list(&filteredList);
	}
	else if (cmd == '2') {
		char key[20];
		printf("\nGive type: ");
		scanf("%s", key);

		dynamicList filteredList = filter_list(dList, "destination", key);
		for (int i = 0; i < filteredList.currentSize; ++i) {
			Offer currentOffer = get_offer(&filteredList, i + 1);
			printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
		}
		destroy_list(&filteredList);
	}
	if (cmd == '3') {
		char key[20];
		printf("\nGive type: ");
		scanf("%s", key);

		dynamicList filteredList = filter_list(dList, "price", key);
		for (int i = 0; i < filteredList.currentSize; ++i) {
			Offer currentOffer = get_offer(&filteredList, i + 1);
			printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
		}
		destroy_list(&filteredList);
	}
}

/*
* Starts the UI sequence
*/
void startUI() {
	dynamicList dList = create_list(2);

	while (1) {
		print_menu();
		char cmd = get_command();
		if (cmd == 'x' || cmd == 'X') {
			printf("\nBye...");
			break;
		}
		else if (cmd == '1') {
			add_new_offer(&dList);
		}
		else if (cmd == '2') {
			change_offer(&dList);
		}
		else if (cmd == '3') {
			delete_offer(&dList);
		}
		else if (cmd == '4') {
			print_sorted(&dList);
		}
		else if (cmd == '5') {
			print_filtered(&dList);
		}
		else if (cmd == 'p' || cmd == 'P') {
			for (int i = 0; i < dList.currentSize; ++i) {
				Offer currentOffer = get_offer(&dList, i + 1);
				printf("\n%s | %s | %s | %d", currentOffer.type, currentOffer.destination, currentOffer.departDate, currentOffer.price);
			}
		}
		else {
			printf("\nWrong input! ");
		}
	}
	destroy_list(&dList);
}

int main() {

	run_tests();
	
	//startUI();

	_CrtDumpMemoryLeaks();

	return 0;
}
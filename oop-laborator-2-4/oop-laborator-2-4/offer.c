#include <assert.h>
#include <stdio.h>
#include "offer.h"

/*
* Creates a new offer using the properties given by parameters
* The parameters have been previously validated
* Input:
*	type - the type of the offer(munte, mare, city break)
*	destination - the destination of the offer
*	departDate - the date of the offer
*	price - the price of the offer
* Output:
*	off - the resulted offer object
*/
Offer create_offer(char type[20], char destination[20], char departDate[20], char price[20]) {
	Offer off;

	off.type = (char *)malloc((strlen(type) + 1) * sizeof(char));
	off.destination = (char *)malloc((strlen(destination) + 1) * sizeof(char));
	off.departDate = (char *)malloc((strlen(departDate) + 1) * sizeof(char));

	off.price = atoi(price);

	strcpy(off.type, type);
	strcpy(off.destination, destination);
	strcpy(off.departDate, departDate);

	return off;
}

/*
* Destroys the pet by deallocating the memory it ocupies
* Input:
*	off - the offer to be destroyed
*/
void destroy_offer(Offer* off) {
	free(off->departDate);
	free(off->destination);
	free(off->type);

	off->type = NULL;
	off->destination = NULL;
	off->departDate = NULL;
	off->type = -1;
}

/*
* Returns a deep-copy of the offer given by paramter
*/
Offer copy_offer(Offer* off) {
	char price[20];
	sprintf(price, "%d", off->price);
	return create_offer(off->type, off->destination, off->departDate, price);
}

void test_create_offer() {
	char type[20] = "munte", destination[20] = "Fiji", departDate[20] = "19/05/2018", price[20] = "1900";
	Offer of = create_offer(type, destination, departDate, price);

	assert(strcmp(of.type, "munte") == 0);
	assert(strcmp(of.destination, "Fiji") == 0);
	assert(strcmp(of.departDate, "19/05/2018") == 0);
	assert(of.price == 1900);

	destroy_offer(&of);
}

void test_copy_offer() {
	char type[20] = "munte", destination[20] = "Fiji", departDate[20] = "19/05/2018", price[20] = "1900";
	Offer of = create_offer(type, destination, departDate, price);

	Offer coff = copy_offer(&of);

	assert(strcmp(coff.type, "munte") == 0);
	assert(strcmp(coff.destination, "Fiji") == 0);
	assert(strcmp(coff.departDate, "19/05/2018") == 0);
	assert(coff.price == 1900);

	destroy_offer(&of);
	destroy_offer(&coff);
}
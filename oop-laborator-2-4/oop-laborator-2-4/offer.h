#pragma once
#include <stdlib.h>

typedef struct {
	char* type, destination, depart_date;
	int price;
} Offer;

Offer create_new_offer(char* type, char* destination, char* depart_data, int price) {
	Offer of;
	of.type = malloc(sizeof(char) * )

}
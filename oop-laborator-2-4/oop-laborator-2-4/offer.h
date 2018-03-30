#pragma once

typedef struct {
	char *type, *destination, *departDate;
	int price;
} Offer;

Offer create_offer(char type[20], char destination[20], char departDate[20], char price[20]);

void destroy_offer(Offer* off);

Offer copy_offer(Offer* off);

void test_create_offer();

void test_copy_offer();
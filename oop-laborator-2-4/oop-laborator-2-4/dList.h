#pragma once

#include "offer.h"
#include <stdlib.h>

typedef struct {
	Offer *elems;
	int capacity, currentSize;
} dynamicList;

dynamicList create_list(int capacity);

void destroy_list(dynamicList* list);

dynamicList resize_list(dynamicList* list);

void add_offer(dynamicList *list, Offer offer);

void remove_offer(dynamicList *list, int pos);

Offer replace_offer(dynamicList* list, int pos, Offer newOffer);

Offer get_offer(dynamicList *list, int pos);

dynamicList copy_list(dynamicList* list);

void test_create_list();

void test_resize_list();

void test_add_offer();

void test_remove_offer();

void test_get_offer();

void test_copy_list();

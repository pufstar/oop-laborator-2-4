#pragma once

#include "offer.h"
#include "dList.h"

int validate(char type[20], char destination[20], char departDate[20], char price[20]);

dynamicList sort_by_price(dynamicList* list);

dynamicList sort_by_destination(dynamicList* list);

dynamicList filter_list(dynamicList* list, char criteria[20], char key[20]);

void test_create_offer();

void test_validate();

void test_sort_by_price();

void test_sort_by_destination();

void test_filter_list();
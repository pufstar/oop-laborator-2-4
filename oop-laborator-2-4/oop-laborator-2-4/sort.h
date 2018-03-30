#pragma once

#include "dList.h"

typedef int(*comparisonFunction)(Offer* of1, Offer* of2);

/*
* Sorts the list using a comparison function
* Input:
*	list - the list to be sorted
*	cmp - the comparison function
*/
void sort_list(dynamicList* list, comparisonFunction cmp);
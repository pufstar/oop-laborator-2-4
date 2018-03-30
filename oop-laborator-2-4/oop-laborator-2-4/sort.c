#pragma once

#include "sort.h"
#include "dList.h"

/*
* Sorts a list using a comparison function
* Input:
*	list - the list to be sorted
*	cmp - the comparison function
*/
void sort_list(dynamicList* list, comparisonFunction cmp) {
	for (int i = 1; i <= list->currentSize; ++i) {
		for (int j = i + 1; j <= list->currentSize; ++j) {
			Offer off1 = get_offer(list, i);
			Offer off2 = get_offer(list, j);
			if (cmp(&off1, &off2) > 0) {
				replace_offer(list, i, off2);
				replace_offer(list, j, off1);
			}
		}
	}
}
#include "tests.h"
#include "service.h"
#include "dList.h"

void run_tests() {
	test_create_offer();
	test_copy_offer();
	test_create_list();
	test_resize_list();
	test_copy_list();
	test_add_offer();
	test_remove_offer();
	test_get_offer();
	test_validate();
	test_cmp_price();
	test_cmp_destination();
	test_sort_by_price();
	test_sort_by_destination();
	test_filter_list();
}


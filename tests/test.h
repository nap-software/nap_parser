#include <assert.h> // assert()
#include <stdio.h> // fprintf()
#include <string.h> // strcmp()
#include "../src/nap_parser.h"

#define TESTS_BEGIN \
	int main(void) {

#define TEST_CASE(_n) fprintf(stderr, "Test: %s\n", _n);

#define TESTS_END \
		return 0;\
	}

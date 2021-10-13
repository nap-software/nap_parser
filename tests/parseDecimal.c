#include "test.h"

TESTS_BEGIN

TEST_CASE("It should work properly") {
	unsigned long out = 0;

	assert(nap_parser__parseDecimal("1234", &out));
	assert(out == 1234);
}

TEST_CASE("It should work without output") {
	assert(nap_parser__parseDecimal("1234", NULL));
}

TEST_CASE("It should return false given an empty string") {
	unsigned long out = 0;

	assert(!nap_parser__parseDecimal("", &out));
}

TEST_CASE("It should return false given a string that contains non-numeric characters") {
	unsigned long out = 0;

	assert(!nap_parser__parseDecimal("12a34", &out));
}

TESTS_END
